/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:18:47 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 10:59:19 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINES_H
# define PIPELINES_H

# include "minishell.h"

t_pipeline	*create_pipeline(t_command *cmd_list);
void		free_pipeline(t_pipeline *pipeline);
void		free_pipes(int **pipes, int pipe_count);
int			**create_pipes(int cmd_count);
int			init_pipeline_execution(t_pipeline *pipeline, pid_t **pids);
int			execute_pipeline(t_pipeline *pipeline, t_minishell *shell);
int			can_execute_directly(t_pipeline *pipeline);
void		close_all_pipes(t_pipeline *pipeline);
int			wait_for_commands(t_pipeline *pipeline, pid_t *pids);
int			fork_and_execute_commands(t_pipeline *pipeline, pid_t *pids,
				t_minishell *shell);

#endif
