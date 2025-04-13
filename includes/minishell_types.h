/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:06:57 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/14 00:24:44 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPES_H
# define MINISHELL_TYPES_H
/*
** Environment variable structure for linked list
*/
typedef struct s_env
{
	char				*key;
	char				*value;
	int					custom;
	int					exit_status;
	int					index;
	struct s_env		*next;
}						t_env;

/*
** Main shell structure // To change it
*/
typedef struct s_minishell
{
	bool				force_exit;
	bool				heredoc;
	int					signal;
	t_env				*envs;
}						t_minishell;

/*
** Command structure for parsing and execution
*/

typedef struct s_command
{
	char				*command;
	char				**args;
	char				**full_cmd;
	char				*from_file;
	char				**hdocs_end;
	char				**to_file;
	int					redirect;
	int					input;
	int					output;
	int					redirect_error;
	struct s_command	*next;
}						t_command;

typedef struct s_pipeline
{
	t_command			**commands;
	int					cmd_count;
	int					**pipes;
}						t_pipeline;

typedef struct s_pipe_exec
{
	t_command			*cmd;
	int					**pipes;
	int					cmd_index;
	int					cmd_count;
	char				**envp;
}						t_pipe_exec;

/*
** Redirection flags
*/
# define IN_REDIR 1 /* Input redirection (<) */
# define HEREDOC 2 /* Here document (<<) */
# define OUT_REDIR 4 /* Output redirection (>) */
# define APPEND 8 /* Append redirection (>>) */
#endif
