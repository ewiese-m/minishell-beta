/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:33:29 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 21:33:55 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**init_cmd_table(int capacity)
{
	char	**cmd_table;

	cmd_table = (char **)ft_calloc(capacity, sizeof(char *));
	return (cmd_table);
}

void	skip_whitespace(char *line, int *i)
{
	while (line[*i] == ' ' || (line[*i] >= '\t' && line[*i] <= '\r'))
		(*i)++;
}

void	process_regular_token(char *line, int *i, char **cmd_table, int *count)
{
	char	*token;

	cmd_table[*count] = ft_strdup("");
	if (cmd_table[*count])
	{
		token = ft_tokenize(cmd_table[*count], line, i, (t_env *)cmd_table[0]);
		if (token)
			cmd_table[*count] = token;
	}
}

char	**resize_cmd_table(char **cmd_table, int *count, int *capacity)
{
	if (cmd_table[*count])
	{
		if (++(*count) >= *capacity - 1)
		{
			*capacity = *capacity * 2;
			cmd_table = ft_realloc(cmd_table, *capacity * sizeof(char *));
		}
	}
	return (cmd_table);
}
