/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:26:12 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 01:28:03 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Initialize the garbage collector
 */
void	gc_init(t_gc *gc)
{
	if (!gc)
		return ;
	gc->mem_list = NULL;
	gc->fd_list.fds = NULL;
	gc->fd_list.count = 0;
	gc->fd_list.capacity = 0;
}
