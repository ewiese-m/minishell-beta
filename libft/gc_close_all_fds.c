/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_close_all_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:43:05 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 01:50:10 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Close all tracked file descriptors
 */
void	gc_close_all_fds(t_gc *gc)
{
	int	i;

	if (!gc || !gc->fd_list.fds)
		return ;
	i = 0;
	while (i < gc->fd_list.count)
	{
		if (gc->fd_list.fds[i] > 2)
			close(gc->fd_list.fds[i]);
		i++;
	}
	gc->fd_list.count = 0;
}
