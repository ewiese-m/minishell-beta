/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:45:36 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/16 15:11:25 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_executable(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == -1)
		return (0);
	if (!S_ISREG(file_stat.st_mode))
		return (0);
	if (!(file_stat.st_mode & S_IXUSR))
		return (0);
	return (1);
}

int	is_directory(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == -1)
		return (0);
	return (S_ISDIR(file_stat.st_mode));
}

char	*check_direct_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (is_directory(cmd))
		{
			handle_is_a_directory(cmd);
		}
		if (is_executable(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

void	free_path_array(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

/* We put the message here 1. for norminete
2. because we used it */
int	handle_is_a_directory(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	exit(126);
}
