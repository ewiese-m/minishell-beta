/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:29:59 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/16 12:01:49 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_RESOLUTION_H
# define PATH_RESOLUTION_H

# include "minishell.h"

int		handle_command_not_found(char *cmd);
int		handle_permission_denied(char *path);
int		handle_is_a_directory(char *cmd);
int		handle_fork_error(void);
int		handle_execve_error(char *path);
int		handle_wait_error(void);
int		is_executable(char *path);
int		is_directory(char *path);
char	*check_direct_path(char *cmd);
void	free_path_array(char **paths);
char	**get_paths(char **envp);
char	*check_path_for_executable(char *path, char *cmd);
char	*search_in_path(char *cmd, char **envp);
char	*find_executable(char *cmd, char **envp);

#endif
