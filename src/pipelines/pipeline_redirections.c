/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:00:20 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/08 12:33:09 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Forks and executes each command in the pipeline
 */
int	fork_and_execute_commands(t_pipeline *pipeline, pid_t *pids, char **envp)
{
	int			i;
	t_pipe_exec	exec_data;

	i = 0;
	while (i < pipeline->cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			handle_fork_error();
			return (i);
		}
		else if (pids[i] == 0)
		{
			exec_data.cmd = pipeline->commands[i];
			exec_data.pipes = pipeline->pipes;
			exec_data.cmd_index = i;
			exec_data.cmd_count = pipeline->cmd_count;
			exec_data.envp = envp;
			execute_pipeline_command(&exec_data);
		}
		i++;
	}
	return (i);
}

/**
 * Closes all pipes except those needed for the current command
 */
void	close_other_pipes(int **pipes, int cmd_index, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		if (i != cmd_index - 1 && i != cmd_index)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}
