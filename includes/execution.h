/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:21:08 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/05 18:05:52 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

/* cmd_execution.c */
int			execute_commands(t_command *cmd_list, t_env *env_list);
int			execute_cmd_list(t_command *cmd_list, char **envp, t_env *env_list);
void		free_env_array(char **env_array);

/* exit_status.c */
void		add_exit_status_var(t_env *env_list);
void		update_exit_status(t_env *env_list, int status);
int			get_exit_status(t_env *env_list);

/* env_conversion.c */
char		**ft_create_env_array(t_env *env_list);
int			count_env_vars(t_env *env_list);

/* pipeline_creation.c */
int			**create_pipes(int cmd_count);
void		free_pipes(int **pipes, int count);
t_pipeline	*create_pipeline(t_command *cmd_list);
void		free_pipeline(t_pipeline *pipeline);
int			apply_redirections(t_command *cmd);

/* pipeline_execution.c */
int			init_pipeline_execution(t_pipeline *pipeline, pid_t **pids);
int			execute_pipeline(t_pipeline *pipeline, char **envp);

/* pipeline_utils.c */
int			can_execute_directly(t_pipeline *pipeline);
void		close_all_pipes(t_pipeline *pipeline);
int			wait_for_commands(t_pipeline *pipeline, pid_t *pids);

/* command_execution.c */
void		close_other_pipes(int **pipes, int cmd_index, int cmd_count);
int			setup_redirections(t_command *cmd, int **pipes, int cmd_index,
				int cmd_count);
void		execute_pipeline_command(t_pipe_exec *exec_data);
int			fork_and_execute_commands(t_pipeline *pipeline, pid_t *pids,
				char **envp);

/*char	**prepare_execve_args(char *executable_path, char **full_cmd)*/
char		**prepare_execve_args(char *executable_path, char **full_cmd);
#endif
