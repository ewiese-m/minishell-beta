/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines_redirections.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:18:47 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/30 18:17:36 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINES_REDIRECTIONS_H
# define PIPELINES_REDIRECTIONS_H

# include "minishell.h"

t_pipeline	*create_pipeline(t_command *cmd_list);
void		free_pipeline(t_pipeline *pipeline);
void		free_pipes(int **pipes, int pipe_count);
int			apply_redirections(t_command *cmd);

#endif
