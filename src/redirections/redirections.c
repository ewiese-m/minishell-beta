/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:48:01 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/14 11:21:22 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_output_file(t_command *cmd, int *fd)
{
	int	flags;

	printf("DEBUG [open_output_file]: Abriendo archivo para salida: '%s'\n",
		cmd->to_file ? cmd->to_file[0] : "NULL");
	if (!cmd->to_file || !cmd->to_file[0])
		return (0);
	if (cmd->redirect & APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	*fd = open(cmd->to_file[0], flags, 0644);
	if (*fd == -1)
	{
		//redirections_error_1(cmd->to_file[0]);
		return (1);
	}
	printf("DEBUG [open_output_file]: Flags: %s\n",
		(cmd->redirect & APPEND) ? "O_APPEND" : "O_TRUNC");
	printf("DEBUG [open_output_file]: fd obtenido: %d\n", *fd);
	return (0);
}

static int	handle_output_redirection(t_command *cmd)
{
	int	fd;
	int	status;

	printf("DEBUG [handle_output_redirection]: Manejando redirección de salida\n");
	printf("DEBUG [handle_output_redirection]: Resultado: %d\n", status);
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

	printf("DEBUG [handle_input_redirection]: Valor real de from_file: '%s'\n",
		cmd->from_file ? cmd->from_file : "NULL");

	if (!cmd->from_file || !cmd->from_file[0])
		return (0);
	fd = open(cmd->from_file, O_RDONLY);
	if (fd == -1)
	{
		//redirections_error_1(cmd->from_file);
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
/*
// In src/redirections/redirections.c,
	modify the handle_input_redirection function:
static int	handle_input_redirection(t_command *cmd)
{
	int	fd;
	int	i;

	if (!cmd->from_file || !cmd->from_file[0])
		return (0);
	// Use the last specified input file (POSIX behavior)
	i = 0;
	while (cmd->from_file[i+1])
		i++;
	fd = open(cmd->from_file[i], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->from_file[i], 2);
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
	printf("DEBUG [handle_input_redirection]: Manejando redirección de entrada: '%s'\n",
		cmd->from_file ? cmd->from_file : "NULL");
	printf("DEBUG [handle_input_redirection]: fd obtenido: %d\n", fd);

	return (0);
}
 */
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
	printf("DEBUG [apply_heredoc]: Aplicando heredoc\n");
	printf("DEBUG [apply_heredoc]: from_file: '%s'\n",
    (cmd->redirect & HEREDOC && cmd->from_file) ? cmd->from_file : "NULL");
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
	printf("DEBUG [apply_redirections]: Aplicando redirecciones para cmd: '%s'\n",
		cmd ? (cmd->command ? cmd->command : "NULL") : "NULL");
	printf("DEBUG [apply_redirections]: Flags de redirección: %d\n",
		cmd ? cmd->redirect : 0);
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
