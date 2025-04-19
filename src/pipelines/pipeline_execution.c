/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:11:31 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/19 12:40:00 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Creates the necessary pipes for a pipeline
 * Returns 0 on success, 1 on failure
 */
static int	create_pipes_for_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (pipeline->cmd_count <= 1)
		return (0);
	pipeline->pipes = (int **)malloc(sizeof(int *) * (pipeline->cmd_count - 1));
	if (!pipeline->pipes)
		return (1);
	i = 0;
	while (i < pipeline->cmd_count - 1)
	{
		pipeline->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipeline->pipes[i])
		{
			free_pipes(pipeline->pipes, i);
			pipeline->pipes = NULL;
			return (1);
		}
		if (pipe(pipeline->pipes[i]) == -1)
		{
			free_pipes(pipeline->pipes, i + 1);
			pipeline->pipes = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * Executes a single builtin command directly in the parent process
 * when a pipeline only contains one builtin command with no redirections
 */
static int	execute_single_builtin(t_pipeline *pipeline, t_minishell *shell)
{
	int	status;

	status = execute_builtin(pipeline->commands[0], shell);
	return (status);
}

/**
 * Creates a child process for a command and executes it
 * Returns the PID of the created process, or -1 on error
 */
static pid_t	fork_to_execute_pipeline(t_pipeline *pipeline, int cmd_index,
		t_minishell *shell)
{
	pid_t		pid;
	t_pipe_exec	exec_data;

	pid = fork();
	if (pid == -1)
	{
		handle_fork_error();
		return (-1);
	}
	if (pid == 0)
	{
		exec_data.cmd = pipeline->commands[cmd_index];
		exec_data.pipes = pipeline->pipes;
		exec_data.cmd_index = cmd_index;
		exec_data.cmd_count = pipeline->cmd_count;
		exec_data.envp = shell->env_array;
		exec_data.shell = shell;
		execute_pipeline_command(&exec_data);
		exit(127);
	}
	return (pid);
}

/*
  Executes a pipeline of commands
  Creates pipes, forks processes, and handles execution
  Handle the case of a single builtin command with no redirections
  Create pipes for the pipeline
  Allocate memory for process IDs
  Fork and execute each command
  Handle failed fork
  Close all pipes in the parent process
  Wait for all child processes and get the last command's exit status
  Handle case where not all commands were executed
  Wait for all processes and get the exit status of the last command
*/
int	execute_pipeline(t_pipeline *pipeline, t_minishell *shell)
{
	pid_t	*pids;
	int		i;
	int		status;
	int		last_status;

	if (!pipeline || !pipeline->commands || pipeline->cmd_count <= 0)
		return (1);
	if (pipeline->cmd_count == 1 && is_builtin(pipeline->commands[0]->command)
		&& pipeline->commands[0]->input == 0
		&& pipeline->commands[0]->output == 1)
	{
		return (execute_single_builtin(pipeline, shell));
	}
	if (create_pipes_for_pipeline(pipeline) != 0)
		return (1);
	pids = (pid_t *)malloc(sizeof(pid_t) * pipeline->cmd_count);
	if (!pids)
	{
		if (pipeline->pipes)
			free_pipes(pipeline->pipes, pipeline->cmd_count - 1);
		return (1);
	}
	i = 0;
	while (i < pipeline->cmd_count)
	{
		pids[i] = fork_to_execute_pipeline(pipeline, i, shell);
		if (pids[i] == -1)
			break ;
		i++;
	}
	if (pipeline->pipes)
		close_all_pipes(pipeline);
	if (i < pipeline->cmd_count)
	{
		while (--i >= 0)
			waitpid(pids[i], &status, 0);
		free(pids);
		return (1);
	}
	last_status = wait_for_commands(pipeline, pids);
	free(pids);
	return (last_status);
}
