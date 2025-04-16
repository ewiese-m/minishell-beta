/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:13:50 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/16 14:42:00 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * creates pipes for the pipeline
 */
int	**create_pipes(int cmd_count)
{
	int	**pipes;
	int	i;

	if (cmd_count <= 1)
		return (NULL);
	pipes = (int **)malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			free_pipes(pipes, i);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			free_pipes(pipes, i + 1);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
