/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 23:08:51 by eebert            #+#    #+#             */
/*   Updated: 2024/10/09 12:08:55 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	read_file(int fd, char **line_buffer, char *buffer)
{
	int		read_bytes;
	char	*temp;

	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes <= 0)
	{
		if (read_bytes == -1)
		{
			free(*line_buffer);
			*line_buffer = NULL;
			free(buffer);
		}
		return (read_bytes);
	}
	buffer[read_bytes] = '\0';
	if (*line_buffer == NULL)
		*line_buffer = ft_strndup(buffer, read_bytes);
	else
	{
		temp = ft_strjoin(*line_buffer, buffer);
		free(*line_buffer);
		*line_buffer = temp;
	}
	return (read_bytes);
}

void	handle_zero_case(char **line_buffer)
{
	if (*line_buffer == NULL)
		return ;
	if (**line_buffer == '\0')
	{
		free(*line_buffer);
		*line_buffer = NULL;
	}
}

char	*get_result(char **line_buffer, char *new_line_pos)
{
	char	*line;
	char	*temp;

	if (*line_buffer == NULL || **line_buffer == '\0')
		return (handle_zero_case(line_buffer), NULL);
	if (new_line_pos == NULL)
	{
		line = ft_strndup(*line_buffer, (size_t)ft_strlen(*line_buffer));
		free(*line_buffer);
		*line_buffer = NULL;
		return (line);
	}
	line = ft_strndup(*line_buffer, new_line_pos - *line_buffer + 1);
	temp = ft_strndup(new_line_pos + 1, (size_t)ft_strlen(new_line_pos + 1));
	free(*line_buffer);
	if (line == NULL || temp == NULL)
	{
		free(line);
		free(temp);
		return (NULL);
	}
	*line_buffer = temp;
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
	if (!buffer)
	{
		free(line_buffer);
		line_buffer = NULL;
		return (NULL);
	}
	while (new_line_pos == NULL && bytes_read > 0)
	{
		total_bytes_read += bytes_read;
		bytes_read = read_file(fd, &line_buffer, buffer);
		if (bytes_read == -1)
			return (NULL);
		new_line_pos = ft_strchr(line_buffer + total_bytes_read, '\n');
	}
	return ((free(buffer)), get_result(&line_buffer, new_line_pos));
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("get_next_line.c", O_RDONLY);
// 	while ((line = get_next_line(7)))
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
