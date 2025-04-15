/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:44:02 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 16:11:00 by ewiese-m         ###   ########.fr       */
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

static int	setup_builtin_redirections(t_command *cmd, t_minishell *shell,
		int *out_fd, int *in_fd)
{
	*out_fd = -1;
	*in_fd = -1;
	if (cmd->redirect)
	{
		*out_fd = dup(STDOUT_FILENO);
		shell_track_fd(shell, *out_fd);
		*in_fd = dup(STDIN_FILENO);
		shell_track_fd(shell, *in_fd);
		if (apply_redirections(cmd, shell) != 0)
		{
			if (*out_fd != -1)
				close(*out_fd);
			if (*in_fd != -1)
				close(*in_fd);
			return (1);
		}
	}
	return (0);
}

static void	restore_std_fds(int stdout_fd, int stdin_fd)
{
	if (stdout_fd != -1)
	{
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdout_fd);
	}
	if (stdin_fd != -1)
	{
		dup2(stdin_fd, STDIN_FILENO);
		close(stdin_fd);
	}
}

static int	execute_specific_builtin(t_command *cmd, t_minishell *shell)
{
	if (ft_strcmp(cmd->command, "echo") == 0)
		return (builtin_echo(cmd, shell));
	else if (ft_strcmp(cmd->command, "cd") == 0)
		return (builtin_cd(cmd, shell));
	else if (ft_strcmp(cmd->command, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->command, "export") == 0)
		return (builtin_export(cmd, shell));
	else if (ft_strcmp(cmd->command, "unset") == 0)
		return (builtin_unset(cmd, shell));
	else if (ft_strcmp(cmd->command, "env") == 0)
		return (builtin_env(shell->env_array));
	else if (ft_strcmp(cmd->command, "exit") == 0)
		return (builtin_exit(cmd));
	return (1);
}

int	execute_builtin(t_command *cmd, t_minishell *shell)
{
	int	original_stdout;
	int	original_stdin;
	int	status;

	if (setup_builtin_redirections(cmd, shell, &original_stdout,
			&original_stdin) != 0)
		return (1);
	status = execute_specific_builtin(cmd, shell);
	restore_std_fds(original_stdout, original_stdin);
	return (status);
}
