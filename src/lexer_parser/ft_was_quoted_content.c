/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_was_quoted_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:05:37 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/17 01:37:54 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_was_quoted_content(char *token)
{
	int	spaces;
	int	special_count;
	int	specials;
	int	consecutive;

	if (is_null_or_empty(token))
		return (0);
	if (is_basic_operator(token) || is_single_non_special(token))
		return (0);
	spaces = has_spaces(token);
	special_count = count_special_chars(token);
	specials = (special_count > 0);
	consecutive = has_consecutive_special(token);
	if (has_suspicious_start(token))
		return (1);
	if (spaces && specials)
		return (1);
	if (special_count > 2)
		return (1);
	if (consecutive)
		return (1);
	if (has_mid_quotes(token))
		return (1);
	return (0);
}
