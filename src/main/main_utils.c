/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:51:04 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 16:51:36 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_builtin_command(t_command *cmds, t_minishell *shell)
{
	int	exit_status;

	exit_status = execute_builtin(cmds, shell);
	update_exit_status(shell->envs, exit_status);
	return (exit_status);
}

int	handle_external_command(t_command *cmds, t_minishell *shell)
{
	int	exit_status;

	exit_status = execute_commands(cmds, shell);
	return (exit_status);
}

int	handle_exit_command(t_command *cmds, t_minishell *shell)
{
	int	exit_status;

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

int	process_valid_command(t_command *cmds, t_minishell *shell)
{
	int	exit_status;

	if (ft_strcmp(cmds->command, "exit") == 0)
		exit_status = handle_exit_command(cmds, shell);
	else if (is_builtin(cmds->command) && cmds->next == NULL)
		exit_status = handle_builtin_command(cmds, shell);
	else
		exit_status = handle_external_command(cmds, shell);
	return (exit_status);
}

void	handle_redirect_errors(t_command *cmds)
{
	t_command	*current;

	current = cmds;
	while (current)
	{
		if (current->redirect_error && (current->redirect & IN_REDIR)
			&& current->from_file)
			redirections_error_1(current->from_file);
		current = current->next;
	}
}
