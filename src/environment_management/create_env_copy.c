/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:36:57 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/31 23:21:34 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TODO */

#include "../../includes/minishell.h"

char	**create_env_copy(char **envp)
{
	int		size;
	char	**env_copy;
	int		i;

	size = 0;
	while (envp[size])
		size++;
	env_copy = malloc((size + 10) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}
