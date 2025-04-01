/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:00:13 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/01 11:01:01 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_exit_arg(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	i = 0;
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}
/*
int	validate_quotes(char *str)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	return (!(single_quote || double_quote));
}
*/
int	validate_quotes(char *str)
{
	int		i;
	char	quote_type;
	int		in_quotes;

	i = 0;
	in_quotes = 0;
	quote_type = 0;
	while (str[i])
	{
		if (!in_quotes && (str[i] == '\'' || str[i] == '\"'))
		{
			in_quotes = 1;
			quote_type = str[i];
		}
		else if (in_quotes && str[i] == quote_type)
		{
			in_quotes = 0;
			quote_type = 0;
		}
		i++;
	}
	return (!in_quotes);
}
