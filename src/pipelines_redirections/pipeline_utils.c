/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:47:13 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/31 22:48:42 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Checks if a command can be executed directly without forking
 */
int	can_execute_directly(t_pipeline *pipeline)
{
	return (pipeline->cmd_count == 1
		&& is_builtin(pipeline->commands[0]->command)
		&& pipeline->commands[0]->input == 0
		&& pipeline->commands[0]->output == 1);
}

/**
 * Closes all pipes in the pipeline
 */
void	close_all_pipes(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline || !pipeline->pipes)
		return ;
	i = 0;
	while (i < pipeline->cmd_count - 1)
	{
		close(pipeline->pipes[i][0]);
		close(pipeline->pipes[i][1]);
		i++;
	}
}

/**
 * Waits for all child processes to complete
 */
int	wait_for_commands(t_pipeline *pipeline, pid_t *pids)
{
	int	i;
	int	status;
	int	last_status;

	last_status = 0;
	i = 0;
	while (i < pipeline->cmd_count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
			handle_wait_error();
		else if (i == pipeline->cmd_count - 1)
			last_status = WEXITSTATUS(status);
		i++;
	}
	return (last_status);
}
