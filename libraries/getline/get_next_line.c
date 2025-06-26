/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:14:22 by ybounite          #+#    #+#             */
/*   Updated: 2025/06/21 09:41:01 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strcher(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

static char	*fill_line_buffer(int fd, char *remainder, char *buffer)
{
	ssize_t	read_len;
	char	*tmp;

	while (1)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len < 0)
			return (NULL);
		else if (read_len == 0)
			break ;
		buffer[read_len] = 0;
		if (!remainder)
			remainder = ft_strdup("");
		tmp = remainder;
		remainder = ft_strjoin(tmp, buffer);
		tmp = NULL;
		if (ft_strcher(buffer, '\n'))
			break ;
	}
	return (remainder);
}

static char	*ft_after_new_line(char *line)
{
	char		*save;
	size_t		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	save = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (save[0] == '\0')
		save = NULL;
	line[i + 1] = '\0';
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		save = NULL;
		return (NULL);
	}
	buffer = ft_malloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, save, buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	save = ft_after_new_line(line);
	return (line);
}
