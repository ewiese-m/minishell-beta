/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:26:03 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 01:29:07 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Add a pointer to the garbage collector's tracking list
 */
void	gc_add(t_gc *gc, void *ptr)
{
	t_mem_node	*new_node;

	if (!gc || !ptr)
		return ;
	new_node = (t_mem_node *)malloc(sizeof(t_mem_node));
	if (!new_node)
		return ;
	new_node->ptr = ptr;
	new_node->next = gc->mem_list;
	gc->mem_list = new_node;
}
