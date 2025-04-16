/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:30:14 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/15 18:38:51 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_newline_pos(const char *str, int c)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count] && str[count] != (unsigned char)c)
		count++;
	if (str[count] == (unsigned char)c)
	{
		count++;
		return (count);
	}
	return (0);
}

static char	*extract_remaining(char *line)
{
	char	*remainder;
	int		newline_pos;

	if (!line)
		return (NULL);
	newline_pos = find_newline_pos(line, '\n');
	if (!newline_pos || !line[newline_pos])
	{
		free(line);
		return (NULL);
	}
	remainder = ft_strdup(&line[newline_pos]);
	free(line);
	return (remainder);
}

static char	*extract_line(char *line)
{
	char	*str;
	size_t	end;

	if (!line)
		return (NULL);
	end = find_newline_pos(line, '\n');
	if (!end)
	{
		str = ft_strdup(line);
		return (str);
	}
	else
	{
		str = (char *)malloc((end + 1) * sizeof(char));
		if (!str)
			return (NULL);
		ft_strlcpy(str, line, (end + 1));
		return (str);
	}
}

static char	*read_buffer(int fd, char *read_in)
{
	int		bytes;
	char	*buffer;

	bytes = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!(find_newline_pos(read_in, '\n')) && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		if (bytes)
			read_in = ft_strjoin_free(read_in, buffer);
	}
	free(buffer);
	return (read_in);
}

char	*get_next_line(int fd)
{
	static char	*line[1024];
	char		*next_line;

	next_line = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	line[fd] = read_buffer(fd, line[fd]);
	if (!line[fd])
		return (NULL);
	next_line = extract_line(line[fd]);
	line[fd] = extract_remaining(line[fd]);
	return (next_line);
}
