/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:53:59 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/30 18:19:58 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*create_env_entry(char *name, char *value)
{
	char	*temp;
	char	*new_var;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	new_var = ft_strjoin(temp, value);
	free(temp);
	return (new_var);
}

static int	find_env_var(char *name, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	update_env(char *name, char *value, char **envp)
{
	int		var_index;
	char	*new_var;

	if (!name || !envp)
		return ;
	var_index = find_env_var(name, envp);
	if (var_index == -1)
		return ;
	new_var = create_env_entry(name, value);
	if (!new_var)
		return ;
	free(envp[var_index]);
	envp[var_index] = new_var;
}
