/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execute_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:11:56 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/19 14:04:27 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Sets up pipe redirections for a command in the pipeline
 * Returns 0 on success, 1 on failure
 */
static int	setup_pipe_redirections(t_pipe_exec *exec_data)
{
	if (exec_data->cmd_index > 0 && exec_data->cmd->input == 0)
	{
		if (dup2(exec_data->pipes[exec_data->cmd_index - 1][0], STDIN_FILENO) ==
			-1)
		{
			perror("minishell: dup2");
			return (1);
		}
	}
	if (exec_data->cmd_index < exec_data->cmd_count - 1
		&& exec_data->cmd->output == 1)
	{
		if (dup2(exec_data->pipes[exec_data->cmd_index][1], STDOUT_FILENO) ==
			-1)
		{
			perror("minishell: dup2");
			return (1);
		}
	}
	return (0);
}

/**
 * Closes all pipe file descriptors except those needed by the current command
 */
static void	close_all_unneeded_pipes(t_pipe_exec *exec_data)
{
	int	i;

	i = 0;
	while (i < exec_data->cmd_count - 1)
	{
		if (!(exec_data->cmd_index > 0 && i == exec_data->cmd_index - 1
				&& exec_data->cmd->input == 0))
		{
			close(exec_data->pipes[i][0]);
		}
		if (!(exec_data->cmd_index < exec_data->cmd_count - 1
				&& i == exec_data->cmd_index && exec_data->cmd->output == 1))
		{
			close(exec_data->pipes[i][1]);
		}
		i++;
	}
}

/**
 * Executes a builtin command in a child process
 */
static void	execute_builtin_command(t_pipe_exec *exec_data)
{
	int	status;

	status = execute_builtin(exec_data->cmd, exec_data->shell);
	exit(status);
}

/**
 * Executes an external command in a child process
 */
static void	execute_external_command(t_pipe_exec *exec_data)
{
	char	*executable_path;
	char	**execve_args;

	executable_path = find_executable(exec_data->cmd->command, exec_data->envp);
	if (!executable_path)
	{
		exit(handle_command_not_found(exec_data->cmd->command));
	}
	execve_args = prepare_execve_args(executable_path,
			exec_data->cmd->full_cmd);
	if (!execve_args)
	{
		free(executable_path);
		exit(1);
	}
	execve(executable_path, execve_args, exec_data->envp);
	free(executable_path);
	free(execve_args);
	exit(handle_execve_error(exec_data->cmd->command));
}

/**
 * Executes a single command in the pipeline
 * This function is called in a child process and should not return
 */
void	execute_pipeline_command(t_pipe_exec *exec_data)
{
	close_all_unneeded_pipes(exec_data);
	if (setup_pipe_redirections(exec_data) != 0)
		exit(1);
	if (apply_redirections(exec_data->cmd, exec_data->shell) != 0)
		exit(1);
	if (is_builtin(exec_data->cmd->command))
		execute_builtin_command(exec_data);
	else
		execute_external_command(exec_data);
	exit(127);
}
