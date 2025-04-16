/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:33:11 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 21:52:45 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "minishell.h"

static int	is_redirect(char c)
{
	return (c == '>' || c == '<');
}

static char	*handle_redirect(char *str, char *input, int *index)
{
	int		i;
	char	tmp[2];

	i = *index;
	if (input[i] == '>' && input[i + 1] == '>')
	{
		str = ft_concat_and_free(str, ft_strdup(">>"));
		*index = i + 2;
	}
	else if (input[i] == '<' && input[i + 1] == '<')
	{
		str = ft_concat_and_free(str, ft_strdup("<<"));
		*index = i + 2;
	}
	else
	{
		tmp[0] = input[i];
		tmp[1] = '\0';
		str = ft_concat_and_free(str, ft_strdup(tmp));
		*index = i + 1;
	}
	return (str);
}

static char	*parse_word(char *str, char *input, int *i, t_env *env_list)
{
	while (input[*i] && !is_redirect(input[*i]) && input[*i] != ' ')
	{
		if (input[*i] == '"' || input[*i] == '\'')
			str = handle_quotes(str, input, i, env_list);
		else if (input[*i] == '$')
			str = handle_dollar_sign(str, input, i, env_list);
		else
			str = handle_regular_char(str, input, i);
		if (!input[*i])
			break ;
	}
	return (str);
}

static void	skip_spaces_and_check_redirect(char *input, int *i, int *index)
{
	if (is_redirect(input[*i]))
	{
		*index = *i;
		return ;
	}
	token_skip_whitespace(input, i);
	*index = *i;
}

char	*ft_tokenize(char *str, char *input, int *index, t_env *env_list)
{
	int	i;

	i = *index;
	if (is_redirect(input[i]))
		return (handle_redirect(str, input, index));
	str = parse_word(str, input, &i, env_list);
	skip_spaces_and_check_redirect(input, &i, index);
	return (str);
}
