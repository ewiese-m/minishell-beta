/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_from_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:57:09 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 11:21:10 by ewiese-m         ###   ########.fr       */
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

// Function for use in a shell context where GC is available
void	shell_remove_from_env(t_minishell *shell, char *name)
{
	int	i;
	int	len;

	if (!name || !shell->env_array)
		return ;
	len = ft_strlen(name);
	i = 0;
	while (shell->env_array[i])
	{
		if (is_matching_var(shell->env_array[i], name, len))
		{
			shift_env_entries(shell->env_array, i);
			return ;
		}
		i++;
	}
}

// Legacy function for compatibility
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
