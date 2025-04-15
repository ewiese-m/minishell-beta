/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:17:02 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 19:09:48 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_hdocs(char *hdocs_end)
{
	char	*str;
	char	*delimiter;
	int		fd;

	delimiter = ft_strjoin(hdocs_end, "\n");
	fd = open("Eduardo_ADHD_tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0666);
	write(1, "heredoc> ", 9);
	str = get_next_line(0);
	while (ft_strcmp(str, delimiter))
	{
		write(fd, str, ft_strlen(str));
		free(str);
		write(1, "heredoc> ", 9);
		str = get_next_line(0);
		if (!str)
			break ;
	}
	free(delimiter);
	free(str);
	return (fd);
}

int	apply_heredoc(char **hdocs_end, t_command *cmd)
{
	int	fd;

	if (!access("Eduardo_ADHD_tmp.txt", F_OK))
		unlink("Eduardo_ADHD.txt");
	fd = read_hdocs(hdocs_end[0]);
	close(fd);
	if (hdocs_end[1])
		return (-1);
	cmd->input = open("Eduardo_ADHD.txt", O_RDONLY);
	return (fd);
}
