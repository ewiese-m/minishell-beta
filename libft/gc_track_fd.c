/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_track_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:26:18 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 01:44:59 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Initialize the file descriptor array
 */
static int	gc_init_fd_array(t_gc *gc)
{
	gc->fd_list.capacity = 10;
	gc->fd_list.fds = (int *)malloc(sizeof(int) * gc->fd_list.capacity);
	if (!gc->fd_list.fds)
		return (0);
	return (1);
}

/**
 * Resize the file descriptor array when it's full
 */
static int	gc_resize_fd_array(t_gc *gc)
{
	int	*new_list;
	int	i;

	gc->fd_list.capacity *= 2;
	new_list = (int *)malloc(sizeof(int) * gc->fd_list.capacity);
	if (!new_list)
		return (0);
	i = 0;
	while (i < gc->fd_list.count)
	{
		new_list[i] = gc->fd_list.fds[i];
		i++;
	}
	free(gc->fd_list.fds);
	gc->fd_list.fds = new_list;
	return (1);
}

/**
 * Track a file descriptor for later closing
 */
void	gc_track_fd(t_gc *gc, int fd)
{
	if (!gc || fd < 0)
		return ;
	if (!gc->fd_list.fds)
	{
		if (!gc_init_fd_array(gc))
			return ;
	}
	else if (gc->fd_list.count >= gc->fd_list.capacity)
	{
		if (!gc_resize_fd_array(gc))
			return ;
	}
	gc->fd_list.fds[gc->fd_list.count++] = fd;
}
