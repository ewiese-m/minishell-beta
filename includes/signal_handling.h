/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:22:35 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 10:42:18 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H

# include "minishell.h"

void	ft_signal_ctrl_c(int signal);
void	setup_child_signals(void);
void	ft_signal_heredoc(int signal);
void	register_shell_for_signals(t_minishell *shell);

#endif
