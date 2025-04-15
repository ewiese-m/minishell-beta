/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:26:15 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 01:28:48 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocate memory and track it with the garbage collector
 */
void	*gc_malloc(t_gc *gc, size_t size)
{
	void	*ptr;

	if (!gc)
		return (NULL);
	ptr = malloc(size);
	if (ptr)
		gc_add(gc, ptr);
	return (ptr);
}
