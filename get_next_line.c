/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 23:08:51 by eebert            #+#    #+#             */
/*   Updated: 2024/09/25 23:10:06 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <malloc.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10000000
#endif

int	read_file(int fd, char **lineBuffer, char *buffer)
{
	int		read_bytes;
	char	*temp;

	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes <= 0)
		return (read_bytes);
	buffer[read_bytes] = '\0';
	if (*lineBuffer == NULL)
		*lineBuffer = ft_strndup(buffer, read_bytes);
	else
	{
		temp = ft_strjoin(*lineBuffer, buffer);
		free(*lineBuffer);
		*lineBuffer = temp;
	}
	return (read_bytes);
}

char	*get_result(char **lineBuffer, char *new_line_pos)
{
	char	*line;
	char	*line;
	char	*temp;

	if (new_line_pos == NULL)
	{
		if (*lineBuffer == NULL || **lineBuffer == '\0')
			return (NULL);
		line = ft_strndup(*lineBuffer, (size_t)ft_strlen(*lineBuffer));
		free(*lineBuffer);
		*lineBuffer = NULL;
		return (line);
	}
	line = ft_strndup(*lineBuffer, new_line_pos - *lineBuffer + 1);
	temp = ft_strndup(new_line_pos + 1, (size_t)ft_strlen(new_line_pos + 1));
	free(*lineBuffer);
	*lineBuffer = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line_buffer = NULL;
	char		*buffer;
	int			bytes_read;
	int			total_bytes_read;
	char		*new_line_pos;

	bytes_read = 1;
	total_bytes_read = -1;
	new_line_pos = NULL;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (new_line_pos == NULL && bytes_read > 0)
	{
		total_bytes_read += bytes_read;
		bytes_read = read_file(fd, &line_buffer, buffer);
		new_line_pos = ft_strchr(line_buffer + total_bytes_read, '\n');
	}
	free(buffer);
	return (get_result(&line_buffer, new_line_pos));
}

/*
int	main(void) {
	char *line;
	int fd = open("../big_line_no_nl", O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);
	close(fd);
	return (0);
}
*/