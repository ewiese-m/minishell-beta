/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:16:01 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/07 15:18:02 by ewiese-m         ###   ########.fr       */
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
	return (exit_status);
}

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
