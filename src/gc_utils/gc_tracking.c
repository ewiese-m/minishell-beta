/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_tracking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:40:40 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 16:45:46 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Track file descriptor in the shell's garbage collector
 */
void	shell_track_fd(t_minishell *shell, int fd)
{
	if (!shell || fd < 0)
		return ;
	gc_track_fd(&shell->gc, fd);
}

/**
 * Track string array elements in the garbage collector
 */
static void	track_string_array(t_minishell *shell, char **array)
{
	int	i;

	if (!array)
		return ;
	gc_add(&shell->gc, array);
	i = 0;
	while (array[i])
	{
		gc_add(&shell->gc, array[i]);
		i++;
	}
}

/**
 * Track command redirections in the garbage collector
 */
static void	track_command_redirections(t_minishell *shell, t_command *cmd)
{
	if (cmd->from_file)
		gc_add(&shell->gc, cmd->from_file);
	if (cmd->hdocs_end)
		track_string_array(shell, cmd->hdocs_end);
	if (cmd->to_file)
		track_string_array(shell, cmd->to_file);
}

/**
 * Track all memory allocations in a command structure
 */
void	shell_track_command(t_minishell *shell, t_command *cmd)
{
	if (!shell || !cmd)
		return ;
	gc_add(&shell->gc, cmd);
	if (cmd->command)
		gc_add(&shell->gc, cmd->command);
	if (cmd->args)
		track_string_array(shell, cmd->args);
	if (cmd->full_cmd)
		track_string_array(shell, cmd->full_cmd);
	track_command_redirections(shell, cmd);
	if (cmd->next)
		shell_track_command(shell, cmd->next);
}

/**
 * Track all memory allocations in environment variables
 */
void	shell_track_env(t_minishell *shell, t_env *env)
{
	if (!shell || !env)
		return ;
	gc_add(&shell->gc, env);
	if (env->key)
		gc_add(&shell->gc, env->key);
	if (env->value)
		gc_add(&shell->gc, env->value);
	if (env->next)
		shell_track_env(shell, env->next);
}
