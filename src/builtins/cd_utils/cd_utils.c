/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:36:18 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 16:36:35 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_pwd_index(char **env_array)
{
	int	i;

	i = 0;
	while (env_array[i])
	{
		if (ft_strncmp(env_array[i], "PWD=", 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	add_new_pwd(t_minishell *shell, char *cwd)
{
	char	*pwd_entry;
	int		i;

	pwd_entry = shell_strjoin(shell, "PWD=", cwd);
	if (!pwd_entry)
		return ;
	i = 0;
	while (shell->env_array[i])
		i++;
	shell->env_array[i] = pwd_entry;
	shell->env_array[i + 1] = NULL;
}
