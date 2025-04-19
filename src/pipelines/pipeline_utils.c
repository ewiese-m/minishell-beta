/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:47:13 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/19 11:29:09 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Free pipe file descriptors
 */
void	free_pipes(int **pipes, int pipe_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		if (pipes[i])
		{
			free(pipes[i]);
			pipes[i] = NULL;
		}
		i++;
	}
	free(pipes);
}

/**
 * Close all pipes in the pipeline
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
 * Extract exit status from process termination status
 * Merci massimo for the tip.
 */
static int	parse_exit_status_grazie_massimo(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

/**
 * Wait for all child processes to complete
 * and return the last command's exit status
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
			last_status = parse_exit_status_grazie_massimo(status);
		i++;
	}
	return (last_status);
}
