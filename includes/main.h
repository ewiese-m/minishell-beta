/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:22:30 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/05 18:18:38 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "minishell.h"

/*
** Main program functions
*/
int	main(int argc, char **argv, char **envp);
int	process_command(char *line, t_env *env_list, char **env_copy);

#endif
