/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:11:56 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/13 20:57:42 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Sets up input/output redirections for a command
 */
int	setup_redirections(t_command *cmd, int **pipes, int cmd_index,
		int cmd_count)
{
	printf("DEBUG [setup_redirections]: Configurando redirecciones para cmd '%s', index %d\n",
		cmd->command ? cmd->command : "NULL", cmd_index);
	if (cmd_index > 0 && cmd->input == 0)
	{
		if (dup2(pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
		printf("DEBUG [setup_redirections]: dup2 resultado: %d\n",
			cmd_index > 0 && cmd->input == 0 ? "stdin desde pipe" : "stdin normal");
			return (1);
	}
	if (cmd_index < cmd_count - 1 && cmd->output == 1)
	{
		if (dup2(pipes[cmd_index][1], STDOUT_FILENO) == -1)
		printf("DEBUG [setup_redirections]: dup2 resultado: %d\n",
			cmd_index < cmd_count - 1 && cmd->output == 1 ? "stdout hacia pipe" : "stdout normal");
			return (1);
	}
	return (apply_redirections(cmd));
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
	printf("DEBUG [prepare_execve_args]: Preparando args para '%s'\n", executable_path);
	printf("DEBUG [prepare_execve_args]: Cantidad de argumentos: %d\n", arg_count);
	return (execve_args);
}
