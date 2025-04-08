/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:11:01 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/08 12:16:58 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*create_env_string(t_env *current)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(current->key, "=");
	result = ft_strjoin(tmp, current->value);
	free(tmp);
	return (result);
}

static int	populate_env_array(char **env_array, t_env *env_list)
{
	int		i;
	t_env	*current;

	i = 0;
	current = env_list;
	while (current)
	{
		if (current->key[0] != '?' && current->value)
		{
			env_array[i] = create_env_string(current);
			if (!env_array[i])
			{
				free_env_array(env_array);
				return (-1);
			}
			i++;
		}
		current = current->next;
	}
	env_array[i] = NULL;
	return (0);
}

static int	count_env_vars(t_env *env_list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		if (current->key[0] != '?' && current->value)
			count++;
		current = current->next;
	}
	return (count);
}

char	**ft_create_env_array(t_env *env_list)
{
	int		count;
	char	**env_array;
	int		status;
	int		extra_space;
	int		i;

	count = count_env_vars(env_list);
	extra_space = 1000;
	env_array = (char **)malloc(sizeof(char *) * (count + extra_space + 1));
	if (!env_array)
		return (NULL);
	status = populate_env_array(env_array, env_list);
	if (status == -1)
		return (NULL);
	i = count;
	while (i < count + extra_space)
		env_array[i++] = NULL;
	return (env_array);
}
