/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:10:41 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/08 12:05:42 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Main entry point for command execution
 */
int	execute_commands(t_command *cmd_list, t_env *env_list)
{
	char	**env_array;
	int		exit_status;

	if (!cmd_list || !env_list)
		return (0);
	env_array = ft_create_env_array(env_list);
	if (!env_array)
		return (1);
	exit_status = execute_cmd_list(cmd_list, env_array, env_list);
	update_exit_status(env_list, exit_status);
	free_env_array(env_array);
	return (exit_status);
}

/**
 * Executes a list of commands through a pipeline
 */
int	execute_cmd_list(t_command *cmd_list, char **envp, t_env *env_list)
{
	t_pipeline	*pipeline;
	int			exit_status;

	if (!cmd_list)
		return (0);
	pipeline = create_pipeline(cmd_list);
	if (!pipeline)
		return (1);
	exit_status = execute_pipeline(pipeline, envp);
	free_pipeline(pipeline);
	update_exit_status(env_list, exit_status);
	return (exit_status);
}
