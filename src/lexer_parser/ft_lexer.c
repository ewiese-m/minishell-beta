/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:33:29 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 21:47:10 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_line_tokens(char *line, char **cmd_table, int *count,
		int *capacity)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
			i++;
		if (!line[i])
			break ;
		if (line[i] == '<' || line[i] == '>')
			ft_handle_redirection(line, &i, cmd_table, count);
		else
			process_regular_token(line, &i, cmd_table, count);
		cmd_table = resize_cmd_table(cmd_table, count, capacity);
	}
}

char	**ft_lexer(char *line, t_env *env_list)
{
	char	**cmd_table;
	int		count;
	int		capacity;

	if (!line)
		return (NULL);
	capacity = 10;
	count = 1;
	cmd_table = init_cmd_table(capacity);
	if (!cmd_table)
		return (NULL);
	cmd_table[0] = (char *)env_list;
	process_line_tokens(line, cmd_table, &count, &capacity);
	cmd_table[count] = NULL;
	return (cmd_table);
}
