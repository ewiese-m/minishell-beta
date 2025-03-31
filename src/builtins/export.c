/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:05:53 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/31 23:12:42 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	update_existing_env_var(char **envp, char *arg)
{
	char	*name;
	char	*eq_pos;
	int		i;
	int		name_len;

	eq_pos = ft_strchr(arg, '=');
	name_len = eq_pos - arg;
	name = ft_substr(arg, 0, name_len);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(arg);
			free(name);
			return (0);
		}
		i++;
	}
	free(name);
	return (1);
}

static int	add_new_env_var(char **envp, char *arg)
{
	int	size;

	size = get_env_size(envp);
	envp[size] = ft_strdup(arg);
	envp[size + 1] = NULL;
	return (0);
}

static int	handle_export_arg(char **envp, char *arg)
{
	if (!is_valid_export_name(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (!ft_strchr(arg, '='))
		return (0);
	if (update_existing_env_var(envp, arg) != 0)
		return (add_new_env_var(envp, arg));
	return (0);
}

static void	print_envp_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

int	builtin_export(t_command *cmd, char **envp)
{
	int	i;
	int	status;

	if (!cmd->args[1])
	{
		print_envp_vars(envp);
		return (0);
	}
	status = 0;
	for (i = 1; cmd->args[i]; i++)
	{
		if (handle_export_arg(envp, cmd->args[i]) != 0)
			status = 1;
	}
	return (status);
}
