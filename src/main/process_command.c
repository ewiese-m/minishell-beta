/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:16:01 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/14 11:21:22 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_exit_command(t_command *cmds)
{
	int	exit_status;

	exit_status = builtin_exit(cmds);
	return (exit_status);
}

static int	handle_builtin_command(t_command *cmds, t_env *env_list,
		char **env_copy)
{
	int	exit_status;

	exit_status = execute_builtin(cmds, env_copy);
	update_exit_status(env_list, exit_status);
	return (exit_status);
}

static int	handle_external_command(t_command *cmds, t_env *env_list)
{
	int	exit_status;

	exit_status = execute_commands(cmds, env_list);
	return (exit_status);
}

static int	process_valid_command(t_command *cmds, t_env *env_list,
		char **env_copy)
{
	int	exit_status;
	printf("DEBUG [process_command]: Llamando a process_valid_command\n");
	if (ft_strcmp(cmds->command, "exit") == 0)
	{
		exit_status = handle_exit_command(cmds);
	}
	else if (is_builtin(cmds->command) && cmds->next == NULL)
	{
		exit_status = handle_builtin_command(cmds, env_list, env_copy);
	}
	else
	{
		exit_status = handle_external_command(cmds, env_list);
	}
	printf("DEBUG [process_command]: process_valid_command retornó: %d\n", exit_status);
	return (exit_status);
}
/*
TODO hacer el control entre pipes/redirecciones.
*/
int	process_command(char *line, t_env *env_list, char **env_copy)
{
	printf("DEBUG [process_command]: Procesando comando: '%s'\n", line);
	t_command	*cmds;
	int			exit_status;
	t_command	*current;

	if (!line || *line == '\0')
		return (0);
	add_history(line);
	printf("DEBUG [process_command]: Llamando a parse_input\n");
	cmds = ft_parse_input(line, env_list);
	if (cmds)
	{
		if (cmds->redirect_error)
		{
			current = cmds;
			while (current)
			{
				if (current->redirect_error && (current->redirect & IN_REDIR)
					&& current->from_file)
					redirections_error_1(current->from_file);
				current = current->next;
			}
			if (!cmds->next)
				return (1);
		}
		exit_status = process_valid_command(cmds, env_list, env_copy);
		ft_free_cmdlist(&cmds);
	}
	else
		printf("DEBUG [process_command]: parse_input falló\n");
	free(line);
	return (exit_status);
}
/*  For debug the paxer/lexer part:
int	process_command(char *line, t_env *env_list, char **env_copy)
{
	t_command	*cmds;
	int			exit_status;

	// exit_status = 0;
	if (!line || *line == '\0')
		return (0);
	add_history(line);
	cmds = ft_parse_input(line, env_list);
	if (cmds)
	{
		// display_command_info(cmds);
		exit_status = process_valid_command(cmds, env_list, env_copy);
		ft_free_cmdlist(&cmds);
	}
	free(line);
	return (exit_status);
}
 */
