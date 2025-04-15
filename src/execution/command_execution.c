/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:11:56 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 13:08:18 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Sets up input/output redirections for a command
 */
int	setup_redirections(t_pipe_exec *exec_data)
{
	if (exec_data->cmd_index > 0 && exec_data->cmd->input == 0)
	{
		if (dup2(exec_data->pipes[exec_data->cmd_index - 1][0], STDIN_FILENO) ==
			-1)
			return (1);
	}
	if (exec_data->cmd_index < exec_data->cmd_count - 1
		&& exec_data->cmd->output == 1)
	{
		if (dup2(exec_data->pipes[exec_data->cmd_index][1], STDOUT_FILENO) ==
			-1)
			return (1);
	}
	return (apply_redirections(exec_data->cmd, exec_data->shell));
}

char	**prepare_execve_args(char *executable_path, char **full_cmd)
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
