/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:48:01 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 00:44:28 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static int	open_output_file(t_command *cmd, int *fd)
{
	int	flags;

	if (!cmd->to_file || !cmd->to_file[0])
		return (0);
	if (cmd->redirect & APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	*fd = open(cmd->to_file[0], flags, 0644);
	if (*fd == -1)
	{
		return (1);
	}
	return (0);
}
 */

static int	handle_output_redirection(t_command *cmd)
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
		i++;
	}
	if (fd != -1)
	{
		cmd->output = dup(STDOUT_FILENO);
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

static int	handle_input_redirection(t_command *cmd)
{
	int	fd;

	if (!cmd->from_file || !cmd->from_file[0])
		return (0);
	fd = open(cmd->from_file, O_RDONLY);
	if (fd == -1)
	{
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	apply_heredoc(t_command *cmd)
{
	int	fd;

	if (cmd->redirect & HEREDOC && cmd->from_file && cmd->from_file[0])
	{
		fd = open(cmd->from_file, O_RDONLY);
		if (fd == -1)
			return (1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	apply_redirections(t_command *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->redirect & IN_REDIR)
	{
		if (handle_input_redirection(cmd) != 0)
			return (1);
	}
	else if (cmd->redirect & HEREDOC)
	{
		if (apply_heredoc(cmd) != 0)
			return (1);
	}
	if (cmd->redirect & OUT_REDIR || cmd->redirect & APPEND)
	{
		if (handle_output_redirection(cmd) != 0)
			return (1);
	}
	return (0);
}
