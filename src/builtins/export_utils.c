/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:05:53 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/31 17:48:18 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_name_part(char *name)
{
	int	i;

	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_export_name(char *arg)
{
	char	*name;
	int		is_valid;

	if (!ft_strchr(arg, '='))
		return (1);
	name = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	is_valid = is_valid_name_part(name);
	free(name);
	return (is_valid);
}

void	print_single_var(t_env *var)
{
	printf("declare -x %s=\"%s\"\n", var->key, var->value);
}

void	print_env_vars(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		print_single_var(current);
		current = current->next;
	}
}
