/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:48:01 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 19:11:20 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_redirections(t_command *cmd, t_minishell *shell)
{
	int	i;

	i = -1;
	if (!cmd)
		return (0);
	if (cmd->redirect & IN_REDIR)
	{
		if (handle_input_redirection(cmd, shell) != 0)
			return (1);
	}
	else if (cmd->redirect & HEREDOC)
	{
		if (apply_heredoc(&cmd->hdocs_end[++i], cmd) != 0)
			return (1);
	}
	if (cmd->redirect & OUT_REDIR || cmd->redirect & APPEND)
	{
		if (handle_output_redirection(cmd, shell) != 0)
			return (1);
	}
	return (0);
}
