/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:10:41 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/13 21:01:31 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Main entry point for command execution
 */
int	execute_commands(t_command *cmd_list, t_env *env_list)
{
	char	**env_array;
	int		exit_status;

	printf("DEBUG [execute_commands]: Iniciando ejecución de comandos\n");
	if (!cmd_list || !env_list)
		return (0);
	env_array = ft_create_env_array(env_list);
	if (!env_array)
		return (1);
	printf("DEBUG [execute_commands]: env_array creado\n");
	printf("DEBUG [execute_commands]: Llamando a execute_cmd_list\n");
	exit_status = execute_cmd_list(cmd_list, env_array, env_list);
	printf("DEBUG [execute_commands]: execute_cmd_list retornó: %d\n", exit_status);
	update_exit_status(env_list, exit_status);
	free_env_array(env_array);
	return (exit_status);
}

/**
 * Executes a list of commands through a pipeline
 */
int	execute_cmd_list(t_command *cmd_list, char **envp, t_env *env_list)
{
	t_pipeline	*pipeline;
	int			exit_status;

	printf("DEBUG [execute_cmd_list]: Creando pipeline\n");
	if (!cmd_list)
		return (0);
	pipeline = create_pipeline(cmd_list);
	if (pipeline)
    	printf("DEBUG [execute_cmd_list]: Pipeline creado con éxito\n");
	else if (!pipeline)
	{
		printf("DEBUG [execute_cmd_list]: Fallo al crear pipeline\n");
		return (1);
	}
	exit_status = execute_pipeline(pipeline, envp);
	free_pipeline(pipeline);
	update_exit_status(env_list, exit_status);
	return (exit_status);
}
