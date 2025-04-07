/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:41:57 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/07 15:36:11 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		is_builtin(char *cmd);
int		execute_builtin(t_command *cmd, char **envp);
int		builtin_echo(t_command *cmd);
int		builtin_cd(t_command *cmd, char **envp);
int		builtin_pwd(void);
int		builtin_export(t_command *cmd, char **envp);
int		builtin_unset(t_command *cmd, char **envp);
int		builtin_env(char **envp);
int		builtin_exit(t_command *cmd);
int		is_valid_name_part(char *name);
int		is_valid_export_name(char *arg);
void	print_single_var(t_env *var);
void	print_env_vars(t_env *env_list);
int		is_valid_exit_arg(char *arg);
int		validate_quotes(char *str);

#endif
