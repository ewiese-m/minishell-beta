/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:18:57 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 16:56:14 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_output_fd(t_command *cmd, int *fd)
{
	int	i;
	int	flags;

	i = 0;
	while (cmd->to_file[i] != NULL)
	{
		if (*fd != -1)
			close(*fd);
		if (cmd->redirect & APPEND)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		*fd = open(cmd->to_file[i], flags, 0644);
		if (*fd == -1)
		{
			perror("minishell: open");
			return (1);
		}
		i++;
	}
	return (0);
}

int	handle_output_redirection(t_command *cmd, t_minishell *shell)
{
	int	fd;

	fd = -1;
	if (!cmd->to_file || !cmd->to_file[0])
		return (0);
	if (setup_output_fd(cmd, &fd) != 0)
		return (1);
	if (fd != -1)
	{
		cmd->output = dup(STDOUT_FILENO);
		shell_track_fd(shell, cmd->output);
		shell_track_fd(shell, fd);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}
