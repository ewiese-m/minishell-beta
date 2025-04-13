/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:16:09 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/13 22:15:54 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(int **pipes, int pipe_count)
{
	int	i;

	printf("DEBUG [free_pipes]: Liberando %d pipes\n", pipe_count);
	if (!pipes)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		if (pipes[i])
		{
			free(pipes[i]);
			pipes[i] = NULL;
		}
		i++;
	}
	free(pipes);
}
