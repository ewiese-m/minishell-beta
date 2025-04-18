/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:22:33 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 12:46:50 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	setup_echo_redirection(t_command *cmd, t_minishell *shell,
		int *original_stdout)
{
	*original_stdout = -1;
	if (cmd->redirect & (OUT_REDIR | APPEND))
	{
		*original_stdout = dup(STDOUT_FILENO);
		if (*original_stdout == -1)
			return (1);
		shell_track_fd(shell, *original_stdout);
		if (apply_redirections(cmd, shell) != 0)
		{
			if (*original_stdout != -1)
				close(*original_stdout);
			return (1);
		}
	}
	return (0);
}

void	restore_stdout(int original_stdout)
{
	if (original_stdout != -1)
	{
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
	}
}
