/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_memory_wrappers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:52:03 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 01:49:11 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Safe strdup - uses garbage collector
 */
char	*safe_strdup(t_gc *gc, const char *s)
{
	char	*dup;
	size_t	len;

	if (!gc || !s)
		return (NULL);
	len = ft_strlen(s);
	dup = (char *)gc_malloc(gc, (len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len + 1);
	return (dup);
}

/**
 * Safe calloc - uses garbage collector
 */
void	*safe_calloc(t_gc *gc, size_t count, size_t size)
{
	void	*ptr;

	if (!gc)
		return (NULL);
	ptr = gc_malloc(gc, count * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}

/**
 * Safe substr - uses garbage collector
 */
char	*safe_substr(t_gc *gc, char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	m_len;
	size_t	i;

	if (!gc || !s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (safe_strdup(gc, ""));
	m_len = s_len - start;
	if (m_len > len)
		m_len = len;
	substr = (char *)gc_malloc(gc, m_len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < m_len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[m_len] = '\0';
	return (substr);
}

/**
 * Safe strjoin - uses garbage collector
 */
char	*safe_strjoin(t_gc *gc, char const *s1, char const *s2)
{
	size_t	len;
	char	*res;

	if (!gc || !s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = (char *)gc_malloc(gc, len * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len);
	ft_strlcat(res, s2, len);
	return (res);
}

/**
 * Clean up and exit the shell with the given status
 */
void	safe_exit(t_gc *gc, int status)
{
	rl_clear_history();
	gc_close_all_fds(gc);
	gc_free_all(gc);
	exit(status);
}
