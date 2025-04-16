/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:26:06 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 16:16:09 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Free all memory tracked by the garbage collector
 */
void	gc_free_all(t_gc *gc)
{
	t_mem_node	*current;
	t_mem_node	*next;

	if (!gc || gc->mem_list)
		return ;
	current = gc->mem_list;
	while (current)
	{
		next = current->next;
		if (current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	gc->mem_list = NULL;
	if (gc->fd_list.fds)
	{
		free(gc->fd_list.fds);
		gc->fd_list.fds = NULL;
	}
	gc->fd_list.count = 0;
	gc->fd_list.capacity = 0;
}
