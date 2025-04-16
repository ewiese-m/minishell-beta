/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:22:23 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 21:43:08 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_redirection_syntax(char **table, int index, int len)
{
	int	count;

	count = 0;
	while (table[index][count] && (table[index][count] == '<'
			|| table[index][count] == '>'))
		count++;
	if (count != len)
		return (printf("syntax error near unexpected token `%c'\n",
				table[index][0]), 1);
	return (0);
}

static int	handle_empty_redirection(char **table, int *index, int *len)
{
	if (table[*index][*len] == '\0')
	{
		*len = 0;
		(*index)++;
		if (table[*index] == NULL)
			return (printf("syntax error near unexpected token `newline'\n"),
				1);
	}
	return (0);
}

static int	ft_handle_input_redirection(t_command *cmd, char **table, int index,
		int len)
{
	int	fd;

	if (cmd->from_file)
		free(cmd->from_file);
	cmd->from_file = ft_strdup(table[index] + len);
	fd = open(cmd->from_file, O_RDONLY);
	if (fd == -1)
	{
		cmd->redirect_error = 1;
		return (0);
	}
	close(fd);
	return (0);
}

static void	handle_other_redirections(t_command *cmd, char **table, int index,
		int len)
{
	if (cmd->redirect & HEREDOC)
		cmd->hdocs_end = ft_many_redirect(cmd->hdocs_end, table[index], len);
	else
		cmd->to_file = ft_many_redirect(cmd->to_file, table[index], len);
}

int	ft_add_redirection(char **table, t_command *cmd, int index, int len)
{
	if (validate_redirection_syntax(table, index, len))
		return (1);
	if (handle_empty_redirection(table, &index, &len))
		return (1);
	if (cmd->redirect & IN_REDIR)
		return (ft_handle_input_redirection(cmd, table, index, len));
	handle_other_redirections(cmd, table, index, len);
	return (0);
}
