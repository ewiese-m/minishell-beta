/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:11:31 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/16 14:40:17 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * handles cleanup and error state in pipeline execution
 */
static int	handle_pipeline_error(t_pipeline *pipeline, pid_t *pids,
		int executed_count)
{
	int	i;
	int	temp_status;

	i = 0;
	while (i < executed_count)
	{
		waitpid(pids[i], &temp_status, 0);
		i++;
	}
	free(pids);
	if (pipeline->pipes)
		free_pipes(pipeline->pipes, pipeline->cmd_count - 1);
	return (1);
}

/**
 * handles cleanup and returns final status for successful execution
 */
static int	handle_pipeline_success(t_pipeline *pipeline, pid_t *pids)
{
	int	last_status;

	last_status = wait_for_commands(pipeline, pids);
	free(pids);
	if (pipeline->pipes)
	{
		free_pipes(pipeline->pipes, pipeline->cmd_count - 1);
		pipeline->pipes = NULL;
	}
	return (last_status);
}

/**
 * initializes the pipeline execution
 */
int	init_pipeline_execution(t_pipeline *pipeline, pid_t **pids)
{
	if (!pipeline || !pipeline->commands || pipeline->cmd_count <= 0)
		return (0);
	pipeline->pipes = create_pipes(pipeline->cmd_count);
	if (pipeline->cmd_count > 1 && !pipeline->pipes)
		return (1);
	*pids = (pid_t *)malloc(sizeof(pid_t) * pipeline->cmd_count);
	if (!*pids)
	{
		if (pipeline->pipes)
			free_pipes(pipeline->pipes, pipeline->cmd_count - 1);
		return (1);
	}
	return (2);
}

/**
 * executes a pipeline of commands
 */
int	execute_pipeline(t_pipeline *pipeline, t_minishell *shell)
{
	pid_t	*pids;
	int		status;
	int		executed_count;

	status = init_pipeline_execution(pipeline, &pids);
	if (status < 2)
		return (status);
	if (can_execute_directly(pipeline))
	{
		status = execute_builtin(pipeline->commands[0], shell);
		free(pids);
		return (status);
	}
	executed_count = fork_and_execute_commands(pipeline, pids, shell);
	if (pipeline->pipes)
		close_all_pipes(pipeline);
	if (executed_count < pipeline->cmd_count)
		return (handle_pipeline_error(pipeline, pids, executed_count));
	return (handle_pipeline_success(pipeline, pids));
}
