/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:35:43 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/05 18:09:07 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	was_quoted_content(char *token)
{
	int	i;

	if (!token)
		return (0);
	i = 0;
	while (token[i])
	{
		if (token[i] == ' ' || token[i] == '<' || token[i] == '>'
			|| token[i] == '*' || token[i] == '|' || token[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

// Get redirection type from token
int	ft_get_redirection(char *token)
{
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
