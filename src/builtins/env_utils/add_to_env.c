/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:56:13 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/07 20:12:26 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_name(char *var)
{
	char	*eq_pos;
	char	*name;

	eq_pos = ft_strchr(var, '=');
	if (!eq_pos)
		return (NULL);
	name = ft_substr(var, 0, eq_pos - var);
	return (name);
}

static int	update_existing_var(char *var, char *name, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0
			&& envp[i][ft_strlen(name)] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	add_new_var(char *var, char **envp)
{
	int	size;

	size = get_env_size(envp);
	envp[size] = ft_strdup(var);
	envp[size + 1] = NULL;
}

void	add_to_env(char *var, char **envp)
{
	char	*name;
	int		updated;

	name = extract_name(var);
	if (!name)
		return ;
	updated = update_existing_var(var, name, envp);
	free(name);
	if (!updated)
		add_new_var(var, envp);
}
