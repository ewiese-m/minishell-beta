/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:33:29 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 21:39:34 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_double_redirect(char *line, int *i, char **cmd_table,
		int *count)
{
	cmd_table[*count] = ft_substr(line, *i, 2);
	*i += 2;
}

static void	handle_single_redirect(char *line, int *i, char **cmd_table,
		int *count)
{
	cmd_table[*count] = ft_substr(line, *i, 1);
	(*i)++;
}

static void	process_post_redirect(char *line, int *i, char **cmd_table,
		int *count)
{
	skip_whitespace(line, i);
	if (line[*i] && line[*i] != '<' && line[*i] != '>')
	{
		(*count)++;
		cmd_table[*count] = ft_strdup("");
		cmd_table[*count] = ft_tokenize(cmd_table[*count], line, i,
				(t_env *)cmd_table[0]);
	}
}

void	ft_handle_redirection(char *line, int *i, char **cmd_table, int *count)
{
	if ((line[*i] == '>' && line[*i + 1] == '>')
		|| (line[*i] == '<' && line[*i + 1] == '<'))
		handle_double_redirect(line, i, cmd_table, count);
	else
		handle_single_redirect(line, i, cmd_table, count);
	process_post_redirect(line, i, cmd_table, count);
}
