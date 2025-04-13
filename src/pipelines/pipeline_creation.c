/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:13:50 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/13 22:20:40 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Creates pipes for the pipeline
 */
int	**create_pipes(int cmd_count)
{
	int	**pipes;
	int	i;
	printf("DEBUG [create_pipes]: Creando pipes para %d comandos\n", cmd_count);

	if (cmd_count <= 1)
		return (NULL);
	pipes = (int **)malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		printf("DEBUG [create_pipes]: Pipe %d creado\n", i);
		if (!pipes[i])
		{
			free_pipes(pipes, i);
			printf("DEBUG [create_pipes]: Error creando pipe %d\n", i);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			free_pipes(pipes, i + 1);
			printf("DEBUG [create_pipes]: Error creando pipe %d\n", i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
