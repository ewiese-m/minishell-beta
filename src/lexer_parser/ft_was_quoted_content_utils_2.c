/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_was_quoted_content_utils_2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:05:37 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/17 01:37:08 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_spaces(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == ' ' || (token[i] >= '\t' && token[i] <= '\r'))
			return (1);
		i++;
	}
	return (0);
}

int	count_special_chars(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i])
	{
		if (is_special_char(token[i]))
			count++;
		i++;
	}
	return (count);
}

int	has_consecutive_special(char *token)
{
	int	i;

	i = 1;
	while (token[i])
	{
		if (is_special_char(token[i - 1]) && is_special_char(token[i])
			&& !is_double_operator(token[i - 1], token[i]))
			return (1);
		i++;
	}
	return (0);
}

int	has_suspicious_start(char *token)
{
	if ((token[0] == '>' || token[0] == '<') && ft_strlen(token) > 1
		&& !is_double_operator(token[0], token[1]))
		return (1);
	if (token[0] == '|' && ft_strlen(token) > 1 && token[1] != '|')
		return (1);
	return (0);
}

int	has_mid_quotes(char *token)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(token);
	while (token[i] && i < len - 1)
	{
		if ((token[i] == '\'' || token[i] == '"')
			&& token[0] != token[i]
			&& token[len - 1] != token[i])
			return (1);
		i++;
	}
	return (0);
}
