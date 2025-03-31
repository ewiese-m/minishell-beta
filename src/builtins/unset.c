/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:59:26 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/26 16:10:53 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	process_unset_arg(char *arg, char **envp)
{
	if (!is_valid_env_name(arg))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	else
	{
		remove_from_env(arg, envp);
	}
	return (0);
}

int	builtin_unset(t_command *cmd, char **envp)
{
	int	i;
	int	status;

	if (!cmd->args[1])
		return (0);
	status = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (process_unset_arg(cmd->args[i], envp) != 0)
			status = 1;
		i++;
	}
	return (status);
}
