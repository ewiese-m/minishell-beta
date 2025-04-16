/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:22:30 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/16 14:21:16 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "minishell.h"

/*
** main program functions
*/
int		main(int argc, char **argv, char **envp);
int		process_command(char *line, t_minishell *shell);

/* main utils */
int		handle_builtin_command(t_command *cmds, t_minishell *shell);
int		handle_external_command(t_command *cmds, t_minishell *shell);
int		handle_exit_command(t_command *cmds, t_minishell *shell);
int		process_valid_command(t_command *cmds, t_minishell *shell);
void	handle_redirect_errors(t_command *cmds);
#endif
