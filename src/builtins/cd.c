/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:58:30 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/31 17:52:16 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_cd_path(t_command *cmd, char **envp)
{
	char	*path;

	if (!cmd->args[1])
	{
		path = get_env_value("HOME", envp);
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

static int	change_directory(char *path)
{
	int	status;

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

static void	update_pwd_env(char **envp)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		update_env("PWD", cwd, envp);
	}
}

int	builtin_cd(t_command *cmd, char **envp)
{
	char	*path;
	int		status;

	path = get_cd_path(cmd, envp);
	if (!path)
		return (1);
	status = change_directory(path);
	if (status == 0)
		update_pwd_env(envp);
	return (status);
}
