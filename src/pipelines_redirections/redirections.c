/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:48:01 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/31 12:34:07 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->to_file[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

static int	handle_output_redirection(t_command *cmd)
{
	int	fd;
	int	status;

	status = open_output_file(cmd, &fd);
	if (status != 0)
		return (status);
	if (!cmd->to_file || !cmd->to_file[0])
		return (0);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->from_file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
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
/*
int	apply_redirections(t_command *cmd)
{
	if (cmd->input != STDIN_FILENO)
	{
		if (dup2(cmd->input, STDIN_FILENO) == -1)
			return (1);
		close(cmd->input);
	}
	if (cmd->output != STDOUT_FILENO)
	{
		if (dup2(cmd->output, STDOUT_FILENO) == -1)
			return (1);
		close(cmd->output);
	}
	return (0);
}
*/
