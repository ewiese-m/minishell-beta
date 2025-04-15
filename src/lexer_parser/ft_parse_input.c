/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:17:04 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 10:25:59 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*skip_leading_whitespace(char *line)
{
	int	token_count;

	token_count = 0;
	while ((line[token_count] && line[token_count] >= 9
			&& line[token_count] <= 13) || line[token_count] == ' ')
		token_count++;
	return (&line[token_count]);
}

static int	is_valid_cmd(t_command *cmd)
{
	if (cmd->command == NULL || strlen(cmd->command) == 0
		|| ft_checkforgarbage(cmd))
		return (0);
	return (1);
}

static void	clean_and_prepare_cmd(t_command *cmd)
{
	ft_removesurplusspaces(cmd);
	ft_create_fullcmd(cmd);
}

static t_command	*handle_parse_error(char *line)
{
	printf("minishell: syntax error near unexpected token `%s'\n", line);
	return (NULL);
}

t_command	*ft_parse_input(char *line, t_minishell *shell)
{
	t_command	*cmd;
	char		*line_copy;
	char		*trimmed_line;

	line_copy = shell_strdup(shell, line);
	if (!line_copy)
		return (NULL);
	trimmed_line = skip_leading_whitespace(line_copy);
	if (*trimmed_line == '\0')
	{
		return (NULL);
	}
	cmd = tokenize_parse_and_link_commands(trimmed_line, shell->envs);
	if (!cmd)
		return (handle_parse_error(line));
	if (!is_valid_cmd(cmd))
	{
		return (NULL);
	}
	clean_and_prepare_cmd(cmd);
	return (cmd);
}
