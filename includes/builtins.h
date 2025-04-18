/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:41:57 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/16 14:25:12 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
/* the builtins asked */

int		is_builtin(char *cmd);
int		execute_builtin(t_command *cmd, t_minishell *shell);
int		builtin_echo(t_command *cmd, t_minishell *shell);
int		builtin_cd(t_command *cmd, t_minishell *shell);
int		builtin_pwd(void);
int		builtin_export(t_command *cmd, t_minishell *shell);
int		builtin_unset(t_command *cmd, t_minishell *shell);
int		builtin_env(char **envp);
int		builtin_exit(t_command *cmd);

/* export utils */
int		is_valid_name_part(char *name);
int		is_valid_export_name(char *arg);
void	print_single_var(t_env *var);
void	print_env_vars(t_env *env_list);
int		is_valid_exit_arg(char *arg);
int		validate_quotes(char *str);
void	print_envp_vars(char **envp);

/* env utils - legacy for compatibility */
int		is_valid_env_name(char *name);
char	*get_env_value(char *name, char **envp);
void	update_env(char *name, char *value, char **envp);
int		get_env_size(char **envp);
void	add_to_env(char *var, char **envp);
void	remove_from_env(char *name, char **envp);

/* shell-managed env utils that use garbage collector */
void	shell_update_env(t_minishell *shell, char *name, char *value);
void	shell_remove_from_env(t_minishell *shell, char *name);

/* echo utils */
int		setup_echo_redirection(t_command *cmd, t_minishell *shell,
			int *original_stdout);
void	restore_stdout(int original_stdout);

/* cd utils */
void	add_new_pwd(t_minishell *shell, char *cwd);
int		find_pwd_index(char **env_array);

#endif
