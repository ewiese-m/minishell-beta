/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:18:47 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/19 10:46:29 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINES_H
# define PIPELINES_H

# include "minishell.h"

/* Pipeline structure functions */
t_pipeline	*create_pipeline(t_command *cmd_list);
void		free_pipeline(t_pipeline *pipeline);

/* Pipeline execution functions */
int			execute_pipeline(t_pipeline *pipeline, t_minishell *shell);
void		execute_pipeline_command(t_pipe_exec *exec_data);

/* Pipeline utility functions */
void		free_pipes(int **pipes, int pipe_count);
void		close_all_pipes(t_pipeline *pipeline);
int			wait_for_commands(t_pipeline *pipeline, pid_t *pids);

#endif
