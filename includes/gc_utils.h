/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:20:35 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 10:19:48 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_UTILS_H
# define GC_UTILS_H

# include "minishell.h"

/* Memory allocation wrappers */
char	*shell_strdup(t_minishell *shell, const char *s);
void	*shell_calloc(t_minishell *shell, size_t count, size_t size);
char	*shell_substr(t_minishell *shell, char const *s, unsigned int start,
			size_t len);
char	*shell_strjoin(t_minishell *shell, char const *s1, char const *s2);

/* Resource tracking functions */
void	shell_track_command(t_minishell *shell, t_command *cmd);
void	shell_track_env(t_minishell *shell, t_env *env);
void	shell_track_fd(t_minishell *shell, int fd);

/* Resource cleanup functions */
void	shell_cleanup(t_minishell *shell, int status);

#endif
