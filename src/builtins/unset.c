/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:59:26 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/16 14:33:18 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * checks if an environment variable matches a name
 */
static int	is_matching_var(char *env_var, char *name, int len)
{
	if (!env_var || !name)
		return (0);
	if (ft_strncmp(env_var, name, len) == 0)
	{
		if (env_var[len] == '=' || env_var[len] == '\0')
			return (1);
	}
	return (0);
}

/**
 * shifts environment entries to remove a variable, verify!
 */
static void	shift_env_entries(char **envp, int start_idx)
{
	int	j;

	if (!envp)
		return ;
	j = start_idx;
	while (envp[j])
	{
		envp[j] = envp[j + 1];
		j++;
	}
}

/**
 * safely removes an environment variable
 */
static void	safe_remove_from_env(t_minishell *shell, char *name)
{
	int	i;
	int	len;

	if (!shell || !name || !shell->env_array)
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

/**
 * processes a single unset argument
 */
static int	process_unset_arg(char *arg, t_minishell *shell)
{
	if (!arg || !shell || !shell->env_array)
		return (1);
	if (!is_valid_env_name(arg))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	else
	{
		safe_remove_from_env(shell, arg);
	}
	return (0);
}

/**
 * implementation of the unset built-in command
 */
int	builtin_unset(t_command *cmd, t_minishell *shell)
{
	int	i;
	int	status;

	if (!cmd || !shell || !shell->env_array)
		return (1);
	if (!cmd->args || !cmd->args[1])
		return (0);
	status = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (process_unset_arg(cmd->args[i], shell) != 0)
			status = 1;
		i++;
	}
	return (status);
}
