/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_was_quoted_content_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:05:37 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/17 01:28:29 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_special_char(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == ';' || c == '*' || c == '?'
		|| c == '[' || c == ']' || c == '(' || c == ')' || c == '&'
		|| c == '#');
}

int	is_double_operator(char a, char b)
{
	return ((a == '>' && b == '>') || (a == '<' && b == '<') || (a == '|'
			&& b == '|') || (a == '&' && b == '&'));
}

int	is_null_or_empty(char *token)
{
	if (!token || token[0] == '\0')
		return (1);
	return (0);
}

int	is_basic_operator(char *token)
{
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0
		|| ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0
		|| ft_strcmp(token, "|") == 0)
		return (1);
	return (0);
}

int	is_single_non_special(char *token)
{
	char	c;

	if (ft_strlen(token) != 1)
		return (0);
	c = token[0];
	if (is_special_char(c) || c == '*')
		return (0);
	return (1);
}
