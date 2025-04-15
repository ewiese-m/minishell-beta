/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:26:09 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 01:34:02 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Free a pointer and remove it from the garbage collector's tracking list
 */
void	gc_free(t_gc *gc, void *ptr)
{
	if (!gc || !ptr)
		return ;
	if (gc_remove(gc, ptr))
		free(ptr);
}
