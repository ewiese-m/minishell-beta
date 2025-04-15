/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:16:01 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 16:32:36 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* static int	handle_exit_command(t_command *cmds, t_minishell *shell)
{
	int	exit_status;

	exit_status = builtin_exit(cmds);
	if (exit_status < -1)
		shell->force_exit = true;
	return (exit_status);
}
 */
static int	handle_builtin_command(t_command *cmds, t_minishell *shell)
{
	int	exit_status;

	exit_status = execute_builtin(cmds, shell);
	update_exit_status(shell->envs, exit_status);
	return (exit_status);
}

static int	handle_external_command(t_command *cmds, t_minishell *shell)
{
	int	exit_status;

	exit_status = execute_commands(cmds, shell);
	return (exit_status);
}

static int	process_valid_command(t_command *cmds, t_minishell *shell)
{
	int	exit_status;

	if (ft_strcmp(cmds->command, "exit") == 0)
	{
		exit_status = builtin_exit(cmds);
		if (exit_status < 0)
		{
			if (exit_status == -1)
				shell_cleanup(shell, 0);
			else if (exit_status == -2)
				shell_cleanup(shell, 2);
			else
				shell_cleanup(shell, -exit_status);
		}
		return (exit_status);
	}
	else if (is_builtin(cmds->command) && cmds->next == NULL)
	{
		exit_status = handle_builtin_command(cmds, shell);
	}
	else
	{
		exit_status = handle_external_command(cmds, shell);
	}
	return (exit_status);
}

int	process_command(char *line, t_minishell *shell)
{
	t_command	*cmds;
	int			exit_status;
	t_command	*current;

	if (!line || *line == '\0')
		return (0);
	cmds = ft_parse_input(line, shell);
	if (cmds)
	{
		shell_track_command(shell, cmds);
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
		exit_status = process_valid_command(cmds, shell);
	}
	else
		exit_status = 0;
	return (exit_status);
}
