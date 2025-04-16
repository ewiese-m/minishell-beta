/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:36:57 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/16 14:36:08 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Here the env space memory is also created.
 */
char	**create_env_copy(t_minishell *shell, char **envp)
{
	int		size;
	char	**env_copy;
	int		extra_space;
	int		i;

	size = 0;
	while (envp[size])
		size++;
	extra_space = 100000;
	env_copy = (char **)gc_malloc(&shell->gc, (size + extra_space + 1)
			* sizeof(char *));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_copy[i] = safe_strdup(&shell->gc, envp[i]);
		if (!env_copy[i])
			return (NULL);
		i++;
	}
	env_copy[i] = NULL;
	while (++i < size + extra_space)
		env_copy[i] = NULL;
	return (env_copy);
}
