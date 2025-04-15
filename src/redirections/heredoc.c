/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:17:02 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 13:17:22 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_heredoc(t_command *cmd, t_minishell *shell)
{
	int	fd;

	if (cmd->redirect & HEREDOC && cmd->from_file && cmd->from_file[0])
	{
		fd = open(cmd->from_file, O_RDONLY);
		if (fd == -1)
			return (1);
		shell_track_fd(shell, fd);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}
