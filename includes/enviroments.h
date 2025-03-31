/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroments.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:00:27 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/27 01:00:48 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENTS_H
# define ENVIROMENTS_H

# include "minishell.h"

int		is_valid_env_name(char *name);
char	*get_env_value(char *name, char **envp);
void	update_env(char *name, char *value, char **envp);
int		get_env_size(char **envp);
void	add_to_env(char *var, char **envp);
void	remove_from_env(char *name, char **envp);
#endif
