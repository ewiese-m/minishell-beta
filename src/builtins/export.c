/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:05:53 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 12:45:39 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Finds an environment variable by name
 * Returns the index of the variable if found, -1 otherwise
 */
static int	find_env_var(char *name, char **envp)
{
	int	i;
	int	name_len;

	if (!name || !envp)
		return (-1);
	name_len = ft_strlen(name);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

/**
 * Updates an existing environment variable
 * Returns 1 if the variable was updated, 0 otherwise
 */
static int	update_existing_env_var(t_minishell *shell, char *arg)
{
	char	*eq_pos;
	char	*name;
	int		var_index;

	if (!shell || !shell->env_array || !arg)
		return (0);
	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
		return (0);
	name = shell_substr(shell, arg, 0, eq_pos - arg);
	if (!name)
		return (0);
	var_index = find_env_var(name, shell->env_array);
	if (var_index >= 0)
	{
		shell->env_array[var_index] = shell_strdup(shell, arg);
		return (1);
	}
	return (0);
}

/**
 * Adds a new environment variable
 */
static int	add_new_env_var(t_minishell *shell, char *arg)
{
	int	size;

	if (!shell || !shell->env_array || !arg)
		return (1);
	size = 0;
	while (shell->env_array[size])
		size++;
	shell->env_array[size] = shell_strdup(shell, arg);
	shell->env_array[size + 1] = NULL;
	return (0);
}

/**
 * Handles a single export argument
 */
static int	handle_export_arg(t_minishell *shell, char *arg)
{
	if (!shell || !arg)
		return (1);
	if (!is_valid_export_name(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (!ft_strchr(arg, '='))
		return (0);
	if (!update_existing_env_var(shell, arg))
		return (add_new_env_var(shell, arg));
	return (0);
}

/**
 * Implementation of the export built-in command
 */
int	builtin_export(t_command *cmd, t_minishell *shell)
{
	int	i;
	int	status;

	if (!cmd || !shell || !shell->env_array)
		return (1);
	if (!cmd->args || !cmd->args[1])
	{
		print_envp_vars(shell->env_array);
		return (0);
	}
	status = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (handle_export_arg(shell, cmd->args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}
