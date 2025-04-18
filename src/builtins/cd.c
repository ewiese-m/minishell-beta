/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:58:30 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/16 14:27:37 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * gets the path to change directory to, idk if its correct.
 */
static char	*get_cd_path(t_command *cmd, t_minishell *shell)
{
	char	*path;

	if (!cmd || !shell || !shell->env_array)
		return (NULL);
	if (!cmd->args[1])
	{
		path = get_env_value("HOME", shell->env_array);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (path);
	}
	else if (cmd->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (NULL);
	}
	return (cmd->args[1]);
}

/**
 * changes the current directory
 */
static int	change_directory(char *path)
{
	int	status;

	if (!path)
		return (1);
	status = chdir(path);
	if (status == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

/**
 * updates the PWD environment variable
 */
static void	update_pwd_env(t_minishell *shell)
{
	char	cwd[PATH_MAX];
	char	*pwd_entry;
	int		pwd_index;

	if (!shell || !shell->env_array)
		return ;
	if (getcwd(cwd, PATH_MAX))
	{
		pwd_index = find_pwd_index(shell->env_array);
		if (pwd_index >= 0)
		{
			pwd_entry = shell_strjoin(shell, "PWD=", cwd);
			if (!pwd_entry)
				return ;
			shell->env_array[pwd_index] = pwd_entry;
		}
		else
			add_new_pwd(shell, cwd);
	}
}

/**
 * implementation of the cd built-in command
 */
int	builtin_cd(t_command *cmd, t_minishell *shell)
{
	char	*path;
	int		status;

	if (!cmd || !shell || !shell->env_array)
		return (1);
	if (cmd->args[1] && ft_strchr(cmd->args[1], ' '))
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	path = get_cd_path(cmd, shell);
	if (!path)
		return (1);
	status = change_directory(path);
	if (status == 0)
		update_pwd_env(shell);
	return (status);
}
