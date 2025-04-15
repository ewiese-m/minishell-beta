/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_management.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:22:24 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 16:06:44 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_MANAGEMENT_H
# define ENVIRONMENT_MANAGEMENT_H

# include "minishell.h"

char	**create_env_copy(t_minishell *shell, char **envp);
void	free_env_array(char **env_array);
char	**free_list(char **list);
t_env	*ft_create_env_node(char *envp, int index);
t_env	*ft_get_envp(char **envp);

#endif
