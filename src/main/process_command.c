/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:16:01 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 16:53:48 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_command(char *line, t_minishell *shell)
{
	t_command	*cmds;
	int			exit_status;

	if (!line || *line == '\0')
		return (0);
	cmds = ft_parse_input(line, shell);
	if (!cmds)
		return (0);
	shell_track_command(shell, cmds);
	if (cmds->redirect_error)
	{
		handle_redirect_errors(cmds);
		if (!cmds->next)
			return (1);
	}
	exit_status = process_valid_command(cmds, shell);
	return (exit_status);
}
