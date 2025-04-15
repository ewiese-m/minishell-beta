/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_close_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:26:03 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 01:41:55 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Close a specific file descriptor and remove it from tracking
 */
void	gc_close_fd(t_gc *gc, int fd)
{
	int	i;
	int	j;

	if (!gc || fd < 0 || !gc->fd_list.fds)
		return ;
	i = 0;
	while (i < gc->fd_list.count)
	{
		if (gc->fd_list.fds[i] == fd)
		{
			close(fd);
			j = i;
			while (j < gc->fd_list.count - 1)
			{
				gc->fd_list.fds[j] = gc->fd_list.fds[j + 1];
				j++;
			}
			gc->fd_list.count--;
			return ;
		}
		i++;
	}
}
