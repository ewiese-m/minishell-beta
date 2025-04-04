/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:36:57 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/04 17:53:23 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**create_env_copy(char **envp)
{
	int		size;
	char	**env_copy;
	int		i;
	int		extra_space;

	size = 0;
	while (envp[size])
		size++;
	extra_space = 10000;
	env_copy = malloc((size + extra_space + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy[i])
		{
			while (--i >= 0)
				free(env_copy[i]);
			free(env_copy);
			return (NULL);
		}
		i++;
	}
	env_copy[i] = NULL;
	while (++i < size + extra_space)
		env_copy[i] = NULL;
	return (env_copy);
}
