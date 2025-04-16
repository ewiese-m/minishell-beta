/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:30:00 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/16 14:53:36 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	setup_signals(void)
{
	signal(SIGINT, ft_signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

static void	minishell_loop(t_minishell *shell)
{
	char	*line;
	int		exit_status;

	while (!shell->force_exit)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		gc_add(&shell->gc, line);
		if (*line)
			add_history(line);
		exit_status = process_command(line, shell);
		if (exit_status < 0)
		{
			update_exit_status(shell->envs, -exit_status);
			shell->exit_status = -exit_status;
			break ;
		}
		else
		{
			update_exit_status(shell->envs, exit_status);
			shell->exit_status = exit_status;
		}
	}
}

/* Check if the error message is correct or not. */
static int	initialize_shell(t_minishell *shell, char **envp)
{
	gc_init(&shell->gc);
	shell->env_array = create_env_copy(shell, envp);
	if (shell->env_array)
		gc_add(&shell->gc, shell->env_array);
	shell->envs = ft_get_envp(envp);
	if (!shell->envs)
	{
		fprintf(stderr, "Error: Failed to initialize environment\n");
		return (1);
	}
	shell_track_env(shell, shell->envs);
	shell->force_exit = false;
	shell->heredoc = false;
	shell->signal = 0;
	shell->exit_status = 0;
	add_exit_status_var(shell->envs);
	return (0);
}

/* Where all the magic begins... */
int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	if (initialize_shell(&shell, envp) != 0)
	{
		shell_cleanup(&shell, 1);
		return (1);
	}
	setup_signals();
	minishell_loop(&shell);
	shell_cleanup(&shell, shell.exit_status);
	return (shell.exit_status);
}
