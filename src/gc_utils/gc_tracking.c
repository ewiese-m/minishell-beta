/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_tracking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:40:40 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 10:21:07 by ewiese-m         ###   ########.fr       */
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
 * Track all memory allocations in a command structure
 */
void	shell_track_command(t_minishell *shell, t_command *cmd)
{
	int	i;

	if (!shell || !cmd)
		return ;
	gc_add(&shell->gc, cmd);
	if (cmd->command)
		gc_add(&shell->gc, cmd->command);
	if (cmd->args)
	{
		gc_add(&shell->gc, cmd->args);
		i = 0;
		while (cmd->args[i])
		{
			gc_add(&shell->gc, cmd->args[i]);
			i++;
		}
	}
	if (cmd->full_cmd)
	{
		gc_add(&shell->gc, cmd->full_cmd);
		i = 0;
		while (cmd->full_cmd[i])
		{
			gc_add(&shell->gc, cmd->full_cmd[i]);
			i++;
		}
	}
	if (cmd->from_file)
		gc_add(&shell->gc, cmd->from_file);
	if (cmd->hdocs_end)
	{
		gc_add(&shell->gc, cmd->hdocs_end);
		i = 0;
		while (cmd->hdocs_end[i])
		{
			gc_add(&shell->gc, cmd->hdocs_end[i]);
			i++;
		}
	}
	if (cmd->to_file)
	{
		gc_add(&shell->gc, cmd->to_file);
		i = 0;
		while (cmd->to_file[i])
		{
			gc_add(&shell->gc, cmd->to_file[i]);
			i++;
		}
	}
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
