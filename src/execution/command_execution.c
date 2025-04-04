/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:11:56 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/04 15:33:01 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**prepare_execve_args(char *executable_path, char **full_cmd)
{
	int		arg_count;
	char	**execve_args;
	int		i;

	arg_count = 0;
	while (full_cmd[arg_count] != NULL)
		arg_count++;
	execve_args = malloc(sizeof(char *) * (arg_count + 1));
	if (!execve_args)
		return (NULL);
	execve_args[0] = executable_path;
	i = 1;
	while (i < arg_count)
	{
		execve_args[i] = full_cmd[i];
		i++;
	}
	execve_args[arg_count] = NULL;
	return (execve_args);
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

/**
 * Sets up input/output redirections for a command
 */
int	setup_redirections(t_command *cmd, int **pipes, int cmd_index,
		int cmd_count)
{
	if (cmd_index > 0 && cmd->input == 0)
	{
		if (dup2(pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
			return (1);
	}
	if (cmd_index < cmd_count - 1 && cmd->output == 0)
	{
		if (dup2(pipes[cmd_index][1], STDOUT_FILENO) == -1)
			return (1);
	}
	return (apply_redirections(cmd));
}

/**
 * Executes a single command in the pipeline
 * Verificar despues el por que de la ejecucion no igual.
 */
void	execute_pipeline_command(t_pipe_exec *exec_data)
{
	char		*executable_path;
	int			status;
	t_pipeline	temp_pipeline;
	int			i;
	char		**execve_args;

	if (setup_redirections(exec_data->cmd, exec_data->pipes,
			exec_data->cmd_index, exec_data->cmd_count) != 0)
	{
		temp_pipeline.pipes = exec_data->pipes;
		temp_pipeline.cmd_count = exec_data->cmd_count;
		close_all_pipes(&temp_pipeline);
		exit(1);
	}
	// Asegurarse de cerrar todos los descriptores de archivo de pipes que este comando no necesita
	for (i = 0; i < exec_data->cmd_count - 1; i++)
	{
		// Este comando necesita pipe[cmd_index-1][0] para lectura (si no es el primer comando)
		// y pipe[cmd_index][1] para escritura (si no es el último comando)
		// Cerrar todos los demás descriptores de archivo de pipes
		if (i != exec_data->cmd_index - 1 || exec_data->cmd_index == 0)
			close(exec_data->pipes[i][0]);
		if (i != exec_data->cmd_index
			|| exec_data->cmd_index == exec_data->cmd_count - 1)
			close(exec_data->pipes[i][1]);
	}
	if (is_builtin(exec_data->cmd->command))
	{
		status = execute_builtin(exec_data->cmd, exec_data->envp);
		exit(status);
	}
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
	// Debug print
	/* 	fprintf(stderr, "DEBUG: execve arguments:\n");
		for (i = 0; execve_args[i] != NULL; i++)
		{
			fprintf(stderr, "  execve_args[%d]: '%s'\n", i, execve_args[i]);
		}
		printf("%s\n", &exec_data->envp);
	*/
	execve(execve_args[0], execve_args, exec_data->envp);
	free(executable_path);
	free(execve_args);
	exit(handle_execve_error(exec_data->cmd->command));
}

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
