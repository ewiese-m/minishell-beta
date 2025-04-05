/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 09:43:39 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/05 18:31:48 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int	g_exit_status;

/* 1. First, Libft */
# include "../libft/libft.h"
/* 2. Second, structure types */
# include "minishell_types.h"
/* 3. main */
# include "main.h"
/* 4. Token & Parser */
# include "lexer_parser.h"
/* 5. Environment management */
# include "environment_management.h"
/* 6. Signal Handling */
# include "signal_handling.h"
/* Minishell enviroment */
# include "enviroments.h"
/* 7. Built-ins */
# include "builtins.h"
/* 8. Execution */
# include "execution.h"
/* 9. Path Resolution */
# include "path_resolution.h"
/* 10. Pipelines and Redirections */
# include "pipelines_redirections.h"

/* Display functions - For testing */
void		display_command_info(t_command *cmds);
void		display_command_name(t_command *cmd);
void		display_arguments(t_command *cmd);
void		display_full_command(t_command *cmd);
void		display_redirections(t_command *cmd);

#endif
