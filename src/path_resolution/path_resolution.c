/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:30:36 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/16 15:09:30 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_path_for_executable(char *path, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_path)
		return (NULL);
	if (is_executable(full_path))
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*search_in_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = check_path_for_executable(paths[i], cmd);
		if (path)
		{
			free_path_array(paths);
			return (path);
		}
		i++;
	}
	free_path_array(paths);
	return (NULL);
}

char	*find_executable(char *cmd, char **envp)
{
	char	*direct_path;

	if (!cmd || !cmd[0])
		return (NULL);
	if (is_builtin(cmd))
		return (ft_strdup(cmd));
	direct_path = check_direct_path(cmd);
	if (direct_path)
		return (direct_path);
	return (search_in_path(cmd, envp));
}
