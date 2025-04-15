/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:26:18 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 01:45:28 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Check if the pointer is at the head of the list
 */
static int	gc_remove_head(t_gc *gc, void *ptr)
{
	t_mem_node	*current;

	if (gc->mem_list->ptr == ptr)
	{
		current = gc->mem_list;
		gc->mem_list = gc->mem_list->next;
		free(current);
		return (1);
	}
	return (0);
}

/**
 * Search for the pointer in the list (excluding the head)
 */
static int	gc_search_and_remove(t_gc *gc, void *ptr)
{
	t_mem_node	*current;
	t_mem_node	*prev;

	prev = gc->mem_list;
	current = gc->mem_list->next;
	while (current)
	{
		if (current->ptr == ptr)
		{
			prev->next = current->next;
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

/**
 * Remove a pointer from the garbage collector's tracking list
 */
int	gc_remove(t_gc *gc, void *ptr)
{
	if (!gc || !ptr || !gc->mem_list)
		return (0);
	if (gc_remove_head(gc, ptr))
		return (1);
	return (gc_search_and_remove(gc, ptr));
}
