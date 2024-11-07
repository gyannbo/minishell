/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:56:45 by msloot            #+#    #+#             */
/*   Updated: 2024/03/10 21:34:08 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	first_newline(const char *buffer)
{
	ssize_t	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static bool	pos_bytes(char *buffer, int fd, ssize_t *n_bytes, char **line)
{
	ssize_t	new_line;

	buffer[*n_bytes] = '\0';
	new_line = first_newline(buffer);
	if (new_line >= 0)
	{
		buffer[new_line] = '\0';
		*line = ft_strjoin_free(*line, buffer, true, false);
		if (!*line)
		{
			*n_bytes = -2;
			return (false);
		}
		buffer = ft_strcpy(buffer, &buffer[new_line + 1]);
		return (true);
	}
	*line = ft_strjoin_free(*line, buffer, true, false);
	if (!*line)
	{
		*n_bytes = -2;
		return (false);
	}
	*n_bytes = read(fd, buffer, BUFFER_SIZE);
	return (false);
}

static char	*find_line(char *buffer, int fd)
{
	char	*line;
	ssize_t	n_bytes;

	if (buffer[0] == '\0')
		n_bytes = read(fd, buffer, BUFFER_SIZE);
	else
		n_bytes = ft_strlen(buffer);
	line = (char *)malloc(sizeof(char) * 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (n_bytes > 0)
	{
		if (pos_bytes(buffer, fd, &n_bytes, &line))
			return (ft_strjoin_free(line, "\n", true, false));
	}
	if (n_bytes == 0 && buffer[0])
	{
		buffer[0] = '\0';
		return (line);
	}
	free(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_SIZE];
	char		*line;

	if (fd < 0 || fd >= FD_SIZE || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[fd] == NULL)
	{
		buffer[fd] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	line = find_line(buffer[fd], fd);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
