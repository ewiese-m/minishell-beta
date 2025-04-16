/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:31:55 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 21:43:43 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
static t_minishell	*g_shell_ptr = NULL;


** Register the shell instance for use in signal handlers

void	register_shell_for_signals(t_minishell *shell)
{
	g_shell_ptr = shell;
}
*/
/*
** Signal handler for CTRL-C (SIGINT)
** This properly handles the interruption and ensures no memory leaks
*/
void	ft_signal_ctrl_c(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}
/*
** Signal handler for child processes
** Sets up different signal handling for child processes

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}


** Signal handler for heredoc CTRL-C
** Handles interruption during heredoc input

void	ft_signal_heredoc(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	if (g_shell_ptr)
		shell_cleanup(g_shell_ptr, 130);
	else
		exit(130);
}
*/