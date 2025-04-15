/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:36:20 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 19:12:48 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*nstr;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
		s1 = (char *)ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	nstr = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!nstr)
		return (NULL);
	ft_strlcpy(nstr, s1, len_s1 + 1);
	ft_strlcpy(&nstr[len_s1], s2, len_s2 + 1);
	free((char *)s1);
	return (nstr);
}
