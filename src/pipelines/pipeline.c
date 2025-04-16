/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:48:33 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/16 14:41:49 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* creacion y inicializacion de pipelines. */

static int	count_commands(t_command *cmd)
{
	int			count;
	t_command	*current;

	count = 0;
	current = cmd;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static t_pipeline	*init_pipeline(t_command *cmd_list)
{
	t_pipeline	*pipeline;

	if (!cmd_list)
		return (NULL);
	pipeline = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->cmd_count = count_commands(cmd_list);
	pipeline->commands = (t_command **)malloc(sizeof(t_command *)
			* pipeline->cmd_count);
	if (!pipeline->commands)
	{
		free(pipeline);
		return (NULL);
	}
	pipeline->pipes = NULL;
	return (pipeline);
}

t_pipeline	*create_pipeline(t_command *cmd_list)
{
	t_pipeline	*pipeline;
	t_command	*current;
	int			i;

	pipeline = init_pipeline(cmd_list);
	if (!pipeline)
		return (NULL);
	current = cmd_list;
	i = 0;
	while (current)
	{
		pipeline->commands[i++] = current;
		current = current->next;
	}
	return (pipeline);
}

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
