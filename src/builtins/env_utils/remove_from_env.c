/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_from_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:57:09 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/07 20:27:49 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_matching_var(char *env_var, char *name, int len)
{
	if (ft_strncmp(env_var, name, len) == 0)
	{
		if (env_var[len] == '=' || env_var[len] == '\0')
			return (1);
	}
	return (0);
}

static void	shift_env_entries(char **envp, int start_idx)
{
	int	j;

	j = start_idx;
	while (envp[j])
	{
		envp[j] = envp[j + 1];
		j++;
	}
}

void	remove_from_env(char *name, char **envp)
{
	int	i;
	int	len;

	if (!name || !envp)
		return ;
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (is_matching_var(envp[i], name, len))
		{
			free(envp[i]);
			shift_env_entries(envp, i);
			return ;
		}
		i++;
	}
}
