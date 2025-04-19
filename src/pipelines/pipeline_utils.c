/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:47:13 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/17 17:23:31 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * checks if a command can be executed directly without forking
 */
int	can_execute_directly(t_pipeline *pipeline)
{
	return (pipeline->cmd_count == 1
		&& is_builtin(pipeline->commands[0]->command)
		&& pipeline->commands[0]->input == 0
		&& pipeline->commands[0]->output == 1);
}

/**
 * closes all pipes in the pipeline
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
 * waits for all child processes to complete
 */

static int	parse_raw_exit_status_massimo(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

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
			last_status = parse_raw_exit_status_massimo(status);
		i++;
	}
	return (last_status);
}
