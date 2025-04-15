/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:53:59 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 12:48:36 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Creates a new environment entry
 */
static char	*create_env_entry(char *name, char *value)
{
	char	*temp;
	char	*new_var;

	if (!name || !value)
		return (NULL);
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	new_var = ft_strjoin(temp, value);
	free(temp);
	return (new_var);
}

/**
 * Finds an environment variable by name
 */
static int	find_env_var(char *name, char **envp)
{
	int	i;
	int	len;

	if (!name || !envp)
		return (-1);
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

/**
 * Function used for updating the environment in a shell context
 */
void	shell_update_env(t_minishell *shell, char *name, char *value)
{
	int		var_index;
	char	*new_var;
	int		i;

	if (!shell || !name || !value || !shell->env_array)
		return ;
	var_index = find_env_var(name, shell->env_array);
	new_var = create_env_entry(name, value);
	if (!new_var)
		return ;
	gc_add(&shell->gc, new_var);
	if (var_index != -1)
	{
		shell->env_array[var_index] = new_var;
	}
	else
	{
		i = 0;
		while (shell->env_array[i])
			i++;
		shell->env_array[i] = new_var;
		shell->env_array[i + 1] = NULL;
	}
}

/**
 * Legacy function for compatibility
 */
void	update_env(char *name, char *value, char **envp)
{
	int		var_index;
	char	*new_var;

	if (!name || !value || !envp)
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
