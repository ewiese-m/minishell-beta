/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:33:11 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/16 12:57:07 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_quotes(char *str, char *input, int *i, t_env *env_list)
{
	char	*result;
	char	quote_type;

	quote_type = input[*i];
	result = ft_process_quotes(str, input, i, env_list);
	if (input[*i] == quote_type)
		(*i)++;
	return (result);
}

char	*handle_dollar_sign(char *str, char *input, int *i, t_env *env_list)
{
	char	*expanded;
	char	*old;

	expanded = ft_extract_env_var(input, i, env_list);
	if (expanded && *expanded == '\0' && *str == '\0')
	{
		free(expanded);
		(*i)++;
		while (input[*i] && (input[*i] == ' ' || (input[*i] >= '\t'
					&& input[*i] <= '\r')))
			(*i)++;
		if (input[*i])
			return (handle_regular_char(str, input, i));
		return (str);
	}
	else if (expanded)
	{
		old = str;
		str = ft_strjoin(str, expanded);
		free(old);
		free(expanded);
	}
	(*i)++;
	return (str);
}

char	*handle_regular_char(char *str, char *input, int *i)
{
	char	tmp[2];
	char	*old;

	tmp[0] = input[*i];
	tmp[1] = '\0';
	old = str;
	str = ft_strjoin(str, tmp);
	free(old);
	(*i)++;
	return (str);
}

void	token_skip_whitespace(char *input, int *i)
{
	while (input[*i] && (input[*i] == ' ' || (input[*i] >= '\t'
				&& input[*i] <= '\r')))
		(*i)++;
}
