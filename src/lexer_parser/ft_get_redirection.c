/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:35:43 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/08 13:12:28 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** This function determines if a token is likely to have come from quoted content.
** It uses multiple heuristics to make this determination:
** 1. Contains whitespace AND special shell characters (likely quoted)
** 2. Contains balanced quotes in the middle (likely quoted)
** 3. Contains multiple special characters in a pattern unlike normal shell syntax
** 4. Has length > 1 and starts with a special character followed by non-whitespace
**    (except for valid operators like >>, <<, etc.)
*/
int	was_quoted_content(char *token)
{
	int	i;
	int	has_spaces;
	int	has_special_chars;
	int	special_char_count;
	int	consecutive_special;

	if (!token || token[0] == '\0')
		return (0);
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0
		|| ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0
		|| ft_strcmp(token, "|") == 0)
	{
		return (0);
	}
	if (ft_strlen(token) == 1 && token[0] != '>' && token[0] != '<'
		&& token[0] != '|' && token[0] != '*' && token[0] != '?'
		&& token[0] != ';')
	{
		return (0);
	}
	i = 0;
	has_spaces = 0;
	has_special_chars = 0;
	special_char_count = 0;
	consecutive_special = 0;
	while (token[i])
	{
		if (token[i] == ' ' || (token[i] >= '\t' && token[i] <= '\r'))
			has_spaces = 1;
		if (token[i] == '<' || token[i] == '>' || token[i] == '|'
			|| token[i] == ';' || token[i] == '*' || token[i] == '?'
			|| token[i] == '[' || token[i] == ']' || token[i] == '('
			|| token[i] == ')' || token[i] == '&' || token[i] == '#')
		{
			has_special_chars = 1;
			special_char_count++;
			if (i > 0 && (token[i - 1] == '<' || token[i - 1] == '>' || token[i
					- 1] == '|' || token[i - 1] == ';' || token[i - 1] == '*'
					|| token[i - 1] == '?' || token[i - 1] == '[' || token[i
					- 1] == ']' || token[i - 1] == '(' || token[i - 1] == ')'
					|| token[i - 1] == '&' || token[i - 1] == '#'))
			{
				if (!((token[i - 1] == '>' && token[i] == '>') || (token[i
							- 1] == '<' && token[i] == '<') || (token[i
							- 1] == '|' && token[i] == '|') || (token[i
							- 1] == '&' && token[i] == '&')))
				{
					consecutive_special = 1;
				}
			}
		}
		i++;
	}
	if (token[0] == '>' || token[0] == '<')
	{
		if (ft_strlen(token) > 2 && !((token[0] == '>' && token[1] == '>')
				|| (token[0] == '<' && token[1] == '<')))
		{
			return (1);
		}
		else if (ft_strlen(token) == 2 && !((token[0] == '>' && token[1] == '>')
				|| (token[0] == '<' && token[1] == '<')))
		{
			return (1);
		}
	}
	if (token[0] == '|' && ft_strlen(token) > 1 && token[1] != '|')
	{
		return (1);
	}
	if (has_spaces && has_special_chars)
	{
		return (1);
	}
	if (special_char_count > 2)
	{
		return (1);
	}
	if (consecutive_special)
	{
		return (1);
	}
	i = 1;
	while (token[i] && i < (int)ft_strlen(token) - 1)
	{
		if ((token[i] == '\'' || token[i] == '"') && (token[0] != token[i]
				&& token[ft_strlen(token) - 1] != token[i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

/* int	ft_get_redirection(char *token)
{
	if (!token)
		return (0);
	if (token[0] == '>')
	{
		if (token[1] == '>')
			return (APPEND);
		return (OUT_REDIR);
	}
	else if (token[0] == '<')
	{
		if (token[1] == '<')
			return (HEREDOC);
		return (IN_REDIR);
	}
	return (0);
}
 */

// Get redirection type from token

// TODO : corregir el ejemplo 13 y 14.
int	ft_get_redirection(char *token)
{
	//if (!token)
	 if (!token || was_quoted_content(token))
		return (0);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(token, "<", 1) == 0)
		return (IN_REDIR);
	if (ft_strncmp(token, ">", 1) == 0)
		return (OUT_REDIR);
	return (0);
}
