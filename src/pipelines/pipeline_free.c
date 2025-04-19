/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:48:33 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/19 11:08:21 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Free a pipeline structure
 */
void	free_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	if (pipeline->commands)
		free(pipeline->commands);
	if (pipeline->pipes)
	{
		free_pipes(pipeline->pipes, pipeline->cmd_count - 1);
		pipeline->pipes = NULL;
	}
	free(pipeline);
}
