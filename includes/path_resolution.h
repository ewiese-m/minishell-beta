/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:29:59 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/31 13:47:55 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_RESOLUTION_H
# define PATH_RESOLUTION_H

# include "minishell.h"

/* Error handling functions */
int		handle_command_not_found(char *cmd);
int		handle_permission_denied(char *path);
int		handle_fork_error(void);
int		handle_execve_error(char *path);
int		handle_wait_error(void);

/* Path resolution functions */
int		is_executable(char *path);
char	*check_direct_path(char *cmd);
void	free_path_array(char **paths);

/* path_env.c */
char	**get_paths(char **envp);

/* path_resolution.c */
char	*check_path_for_executable(char *path, char *cmd);
char	*search_in_path(char *cmd, char **envp);
char	*find_executable(char *cmd, char **envp);

#endif
