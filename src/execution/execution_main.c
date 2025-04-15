/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:10:41 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 13:11:20 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Main entry point for command execution
 */
int	execute_commands(t_command *cmd_list, t_minishell *shell)
{
	int	exit_status;

	if (!cmd_list || !shell)
		return (0);
	exit_status = execute_cmd_list(cmd_list, shell);
	update_exit_status(shell->envs, exit_status);
	return (exit_status);
}

/**
 * Executes a list of commands through a pipeline
 */
int	execute_cmd_list(t_command *cmd_list, t_minishell *shell)
{
	t_pipeline	*pipeline;
	int			exit_status;
	int			i;

	if (!cmd_list)
		return (0);
	pipeline = create_pipeline(cmd_list);
	if (!pipeline)
		return (1);
	gc_add(&shell->gc, pipeline);
	if (pipeline->commands)
		gc_add(&shell->gc, pipeline->commands);
	if (pipeline->pipes)
	{
		i = 0;
		while (i < pipeline->cmd_count - 1)
		{
			if (pipeline->pipes[i])
				gc_add(&shell->gc, pipeline->pipes[i]);
			i++;
		}
		gc_add(&shell->gc, pipeline->pipes);
	}
	exit_status = execute_pipeline(pipeline, shell);
	update_exit_status(shell->envs, exit_status);
	return (exit_status);
}
