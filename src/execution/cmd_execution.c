/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:10:41 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/02 12:56:47 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Main entry point for command execution
 */
int	execute_commands(t_command *cmd_list, t_env *env_list)
{
	char	**env_array;
	int		exit_status;

	if (!cmd_list || !env_list)
		return (0);
	env_array = ft_create_env_array(env_list);
	if (!env_array)
		return (1);
	exit_status = execute_cmd_list(cmd_list, env_array, env_list);
	update_exit_status(env_list, exit_status);
	free_env_array(env_array);
	return (exit_status);
}

/**
 * Executes a list of commands through a pipeline
 */
int	execute_cmd_list(t_command *cmd_list, char **envp, t_env *env_list)
{
	t_pipeline	*pipeline;
	int			exit_status;

	if (!cmd_list)
		return (0);
	pipeline = create_pipeline(cmd_list);
	if (!pipeline)
		return (1);
	exit_status = execute_pipeline(pipeline, envp);
	free_pipeline(pipeline);
	update_exit_status(env_list, exit_status);
	return (exit_status);
}

void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

/**
static t_env	*find_exit_status_var(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, "?") == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

static t_env	*create_exit_status_var(t_env *env_list)
{
	t_env	*current;
	t_env	*exit_status_var;

	current = env_list;
	while (current->next)
	{
		current = current->next;
	}
	exit_status_var = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!exit_status_var)
	{
		return (NULL);
	}
	exit_status_var->key = ft_strdup("?");
	exit_status_var->custom = 1;
	exit_status_var->next = NULL;
	current->next = exit_status_var;
	return (exit_status_var);
}

static void	update_status_value(t_env *exit_status_var, int status)
{
	char	*status_str;

	status_str = ft_itoa(status);
	if (status_str)
	{
		if (exit_status_var->value)
		{
			free(exit_status_var->value);
		}
		exit_status_var->value = status_str;
		exit_status_var->exit_status = status;
	}
}

void	update_exit_status(t_env *env_list, int status)
{
	t_env	*exit_status_var;

	if (!env_list)
	{
		return ;
	}
	exit_status_var = find_exit_status_var(env_list);
	if (!exit_status_var)
	{
		exit_status_var = create_exit_status_var(env_list);
		if (!exit_status_var)
		{
			return ;
		}
	}
	update_status_value(exit_status_var, status);
}
*/
