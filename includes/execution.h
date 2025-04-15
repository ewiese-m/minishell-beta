/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:21:08 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 12:36:12 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

int		execute_commands(t_command *cmd_list, t_minishell *shell);
int		execute_cmd_list(t_command *cmd_list, t_minishell *shell);
void	add_exit_status_var(t_env *env_list);
void	update_exit_status(t_env *env_list, int status);
int		get_exit_status(t_env *env_list);
char	**ft_create_env_array(t_env *env_list);
void	close_other_pipes(int **pipes, int cmd_index, int cmd_count);
int		setup_redirections(t_pipe_exec *exec_data);
void	execute_pipeline_command(t_pipe_exec *exec_data);
char	**prepare_execve_args(char *executable_path, char **full_cmd);

#endif
