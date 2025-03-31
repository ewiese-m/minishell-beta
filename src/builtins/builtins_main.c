/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:44:02 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/31 17:52:10 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	execute_builtin(t_command *cmd, char **envp)
{
	if (ft_strcmp(cmd->command, "echo") == 0)
		return (builtin_echo(cmd));
	else if (ft_strcmp(cmd->command, "cd") == 0)
		return (builtin_cd(cmd, envp));
	else if (ft_strcmp(cmd->command, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->command, "export") == 0)
		return (builtin_export(cmd, envp));
	else if (ft_strcmp(cmd->command, "unset") == 0)
		return (builtin_unset(cmd, envp));
	else if (ft_strcmp(cmd->command, "env") == 0)
		return (builtin_env(envp));
	else if (ft_strcmp(cmd->command, "exit") == 0)
		return (builtin_exit(cmd));
	return (1);
}
