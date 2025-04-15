/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:18:47 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 13:21:27 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "minishell.h"

int		apply_redirections(t_command *cmd, t_minishell *shell);
int		apply_heredoc(t_command *cmd, t_minishell *shell);
int		handle_input_redirection(t_command *cmd, t_minishell *shell);
int		handle_output_redirection(t_command *cmd, t_minishell *shell);
void	redirections_error_1(char *file);

#endif
