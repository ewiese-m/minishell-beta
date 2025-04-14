/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:55:17 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/14 12:23:49 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_n_option(char *arg)
{
	int	j;

	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	j = 1;
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

static int	count_n_options(char **args)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 1;
	while (args[i] && is_valid_n_option(args[i]))
	{
		n_flag++;
		i++;
	}
	return (n_flag);
}

static void	print_echo_args(char **args, int start_index)
{
	while (args[start_index])
	{
		ft_putstr_fd(args[start_index], STDOUT_FILENO);
		if (args[start_index + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		start_index++;
	}
}

int	builtin_echo(t_command *cmd)
{
	int	n_flag;
	int	start_index;
	int	original_stdout;
	int	status;

	status = 0;
	if (setup_echo_redirection(cmd, &original_stdout) != 0)
		return (1);
	n_flag = count_n_options(cmd->args);
	start_index = 1 + n_flag;
	print_echo_args(cmd->args, start_index);
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	restore_stdout(original_stdout);
	return (status);
}
