/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_management.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:22:24 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/31 21:40:03 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_MANAGEMENT_H
# define ENVIROMENT_MANAGEMENT_H

# include "minishell.h"
/*
** Environment management functions
*/
char	**create_env_copy(char **envp);
void	free_env_copy(char **env_copy);
char	**free_list(char **list);
t_env	*ft_create_env_node(char *envp, int index);
t_env	*ft_get_envp(char **envp);

#endif
