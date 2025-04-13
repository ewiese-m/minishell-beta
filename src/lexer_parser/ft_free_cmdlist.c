/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmdlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:20:08 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/13 22:45:24 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_cmdlist(t_command **cmd)
{
	t_command	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		*cmd = (*cmd)->next;
		if (tmp->command)
			free(tmp->command);
		if (tmp->args)
			ft_free_dstr(tmp->args);
		if (tmp->full_cmd)
			ft_free_dstr(tmp->full_cmd);
		if (tmp->redirect & IN_REDIR && tmp->from_file)
			free(tmp->from_file);
		if (tmp->redirect & HEREDOC && tmp->hdocs_end)
			ft_free_dstr(tmp->hdocs_end);
		if ((tmp->redirect & OUT_REDIR || tmp->redirect & APPEND)
			&& tmp->to_file)
			ft_free_dstr(tmp->to_file);
		free(tmp);
		tmp = *cmd;
	}
}
