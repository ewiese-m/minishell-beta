/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:18:57 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 13:19:13 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_output_redirection(t_command *cmd, t_minishell *shell)
{
	int	i;
	int	fd;
	int	flags;

	fd = -1;
	if (!cmd->to_file || !cmd->to_file[0])
		return (0);
	i = 0;
	while (cmd->to_file[i] != NULL)
	{
		if (fd != -1)
			close(fd);
		if (cmd->redirect & APPEND)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(cmd->to_file[i], flags, 0644);
		if (fd == -1)
		{
			perror("minishell: open");
			return (1);
		}
		shell_track_fd(shell, fd);
		i++;
	}
	if (fd != -1)
	{
		cmd->output = dup(STDOUT_FILENO);
		shell_track_fd(shell, cmd->output);
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
