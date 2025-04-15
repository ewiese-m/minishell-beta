/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:11:56 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 12:37:21 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Handles errors in redirection setup
 */
static void	handle_redirection_error(t_pipe_exec *exec_data)
{
	t_pipeline	temp_pipeline;

	temp_pipeline.pipes = exec_data->pipes;
	temp_pipeline.cmd_count = exec_data->cmd_count;
	close_all_pipes(&temp_pipeline);
	exit(1);
}

/**
 * Closes pipe file descriptors not needed by the current command
 */
static void	close_unused_pipes(t_pipe_exec *exec_data)
{
	int	i;

	i = 0;
	while (i < exec_data->cmd_count - 1)
	{
		if (i != exec_data->cmd_index - 1 || exec_data->cmd_index == 0)
			close(exec_data->pipes[i][0]);
		if (i != exec_data->cmd_index
			|| exec_data->cmd_index == exec_data->cmd_count - 1)
			close(exec_data->pipes[i][1]);
		i++;
	}
}

/**
 * Executes builtin commands in the pipeline
 */
static void	execute_builtin_command(t_pipe_exec *exec_data)
{
	int	status;

	status = execute_builtin(exec_data->cmd, exec_data->shell);
	exit(status);
}

/**
 * Executes external commands in the pipeline
 */
static void	execute_external_command(t_pipe_exec *exec_data)
{
	char	*executable_path;
	char	**execve_args;

	executable_path = find_executable(exec_data->cmd->command, exec_data->envp);
	if (!executable_path)
		exit(handle_command_not_found(exec_data->cmd->command));
	execve_args = prepare_execve_args(executable_path,
			exec_data->cmd->full_cmd);
	if (!execve_args)
	{
		free(executable_path);
		exit(1);
	}
	execve(execve_args[0], execve_args, exec_data->envp);
	free(executable_path);
	free(execve_args);
	exit(handle_execve_error(exec_data->cmd->command));
}

/**
 * Executes a single command in the pipeline
 * Verificar despues el por que de la ejecucion no igual.
 */
void	execute_pipeline_command(t_pipe_exec *exec_data)
{
	if (setup_redirections(exec_data) != 0)
		handle_redirection_error(exec_data);
	close_unused_pipes(exec_data);
	if (is_builtin(exec_data->cmd->command))
		execute_builtin_command(exec_data);
	else
		execute_external_command(exec_data);
}
