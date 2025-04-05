/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:36:57 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/05 17:55:32 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_env_copy(char **env_copy, int size, int extra_space,
		char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy[i])
		{
			while (--i >= 0)
				free(env_copy[i]);
			free(env_copy);
			return ;
		}
		i++;
	}
	env_copy[i] = NULL;
	while (++i < size + extra_space)
		env_copy[i] = NULL;
}

char	**create_env_copy(char **envp)
{
	int		size;
	char	**env_copy;
	int		extra_space;

	size = 0;
	while (envp[size])
		size++;
	extra_space = 10000;
	env_copy = malloc((size + extra_space + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	init_env_copy(env_copy, size, extra_space, envp);
	return (env_copy);
}
