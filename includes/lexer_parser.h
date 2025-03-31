/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:22:27 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/30 15:31:00 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

# include "minishell.h"

/*
** Lexer and Parser functions
*/
char		*ft_expand_variable(char *input, t_env *env_list);
char		*ft_extract_env_var(char *in_put, int *index, t_env *env_list);
char		*handle_expansion(char *result, char *input, int *i,
				t_env *env_list);
char		*ft_process_quotes(char *str, char *input, int *index,
				t_env *env_list);
char		**ft_realloc(char **ptr, size_t new_size);
char		*ft_tokenize(char *str, char *input, int *index, t_env *env_list);
char		**ft_lexer(char *line, t_env *env_list);
char		*ft_concat_and_free(char *str1, char *str2);
char		**ft_resize_string_array(char **array, int current_size,
				int target_size);
int			ft_get_redirection(char *token);
void		ft_arrange_table(char **table, int index, int len);
char		*ft_add_io_file(char *old_file, char *new_file,
				int len_redirection);
char		**ft_many_redirect(char **old_files, char *new_file, int len);
int			ft_add_redirection(char **table, t_command *cmd, int index,
				int len);
int			ft_check_redirect(t_command *cmd, char **cmd_table);
void		ft_free_dstr(char **str);
t_command	*ft_parser(char **cmd_table);
int			count_command(char *line);
int			extract_command(char *line, int i, char **cmd);
char		**parse_cmd_into_array(char *line);
void		ft_free_cmdlist(t_command **cmd);
t_command	*ft_many_cmd(t_command *cmd, char **full_cmd, t_env *env_list);
t_command	*tokenize_parse_and_link_commands(char *line, t_env *env_list);
int			ft_checkforgarbage(t_command *cmd);
void		ft_removesurplusspaces(t_command *cmd);
void		ft_create_fullcmd(t_command *cmd);
t_command	*ft_parse_input(char *line, t_env *env_list);

#endif