/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:08:19 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/08 12:05:52 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_exit_status_var(t_env *env_list)
{
	t_env	*current;
	t_env	*exit_var;

	current = env_list;
	exit_var = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, "?") == 0)
			return ;
		if (!current->next)
			break ;
		current = current->next;
	}
	exit_var = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!exit_var)
		return ;
	exit_var->key = ft_strdup("?");
	exit_var->value = ft_strdup("0");
	exit_var->exit_status = 0;
	exit_var->custom = 1;
	exit_var->next = NULL;
	if (current)
		current->next = exit_var;
	else
		env_list = exit_var;
}

/**
 * Updates the exit status in the environment list
 */
void	update_exit_status(t_env *env_list, int status)
{
	t_env	*current;

	if (!env_list)
		return ;
	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, "?") == 0)
		{
			if (current->value)
				free(current->value);
			current->value = ft_itoa(status);
			current->exit_status = status;
			return ;
		}
		current = current->next;
	}
	add_exit_status_var(env_list);
	update_exit_status(env_list, status);
}

int	get_exit_status(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, "?") == 0)
			return (current->exit_status);
		current = current->next;
	}
	return (0);
}
