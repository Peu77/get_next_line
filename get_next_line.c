/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 23:08:51 by eebert            #+#    #+#             */
/*   Updated: 2024/10/09 10:31:23 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

t_list	*insert_chunk(int fd, t_list **chunk_lst)
{
	char	*buffer;
	int		read_bytes;
	t_list	*new_chunk;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes == -1)
		return (free(buffer), -1);
	buffer[read_bytes] = '\0';
	new_chunk = malloc(sizeof(t_list));
	if (!new_chunk)
		return (free(buffer), -1);
	new_chunk->buffer = buffer;
	new_chunk->buffer_size = read_bytes;
	ft_lstadd_back(chunk_lst, new_chunk);
	return (new_chunk);
}

void	free_chunk_lst(t_list **chunk_lst)
{
	t_list	*temp;

	while (*chunk_lst)
	{
		temp = (*chunk_lst)->next;
		free((*chunk_lst)->buffer);
		free(*chunk_lst);
		*chunk_lst = temp;
	}
}

char* get_result(t_list **chunk_lst, char *new_line_pos)
{
	char	*line;
	char	*temp;
}

char	*get_next_line(int fd)
{
	static t_list	*chunk_lst = NULL;
	t_list			*chunk;
	char			*new_line_pos;

	new_line_pos = NULL;
	while (new_line_pos == NULL)
	{
		chunk = insert_chunk(fd, &chunk_lst);
		if (chunk == -1)
			return (free_chunk_lst(&chunk_lst), NULL);
			
		new_line_pos = ft_strchr(chunk->buffer, '\n');
	}
	return (0);
}

int	main(void)
{
	get_next_line(5);
	get_next_line(5);
	get_next_line(5);
}

// int	read_file(int fd, char **line_buffer, char *buffer)
// {
// 	int		read_bytes;
// 	char	*temp;

// 	read_bytes = read(fd, buffer, BUFFER_SIZE);
// 	if (read_bytes <= 0)
// 	{
// 		if (read_bytes == -1)
// 		{
// 			free(*line_buffer);
// 			*line_buffer = NULL;
// 			free(buffer);
// 		}
// 		return (read_bytes);
// 	}
// 	buffer[read_bytes] = '\0';
// 	if (*line_buffer == NULL)
// 		*line_buffer = ft_strndup(buffer, read_bytes);
// 	else
// 	{
// 		temp = ft_strjoin(*line_buffer, buffer);
// 		free(*line_buffer);
// 		*line_buffer = temp;
// 	}
// 	return (read_bytes);
// }

// void	handle_zero_case(char **line_buffer)
// {
// 	if (*line_buffer == NULL)
// 		return ;
// 	if (**line_buffer == '\0')
// 	{
// 		free(*line_buffer);
// 		*line_buffer = NULL;
// 	}
// }

// char	*get_result(char **line_buffer, char *new_line_pos)
// {
// 	char	*line;
// 	char	*temp;

// 	if (*line_buffer == NULL || **line_buffer == '\0')
// 		return (handle_zero_case(line_buffer), NULL);
// 	if (new_line_pos == NULL)
// 	{
// 		line = ft_strndup(*line_buffer, (size_t)ft_strlen(*line_buffer));
// 		free(*line_buffer);
// 		*line_buffer = NULL;
// 		return (line);
// 	}
// 	line = ft_strndup(*line_buffer, new_line_pos - *line_buffer + 1);
// 	temp = ft_strndup(new_line_pos + 1, (size_t)ft_strlen(new_line_pos + 1));
// 	free(*line_buffer);
// 	if (line == NULL || temp == NULL)
// 	{
// 		free(line);
// 		free(temp);
// 		return (NULL);
// 	}
// 	*line_buffer = temp;
// 	return (line);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*line_buffer = NULL;
// 	char		*buffer;
// 	int			bytes_read;
// 	int			total_bytes_read;
// 	char		*new_line_pos;

// 	bytes_read = 1;
// 	total_bytes_read = -1;
// 	new_line_pos = NULL;
// 	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (!buffer)
// 	{
// 		free(line_buffer);
// 		line_buffer = NULL;
// 		return (NULL);
// 	}
// 	while (new_line_pos == NULL && bytes_read > 0)
// 	{
// 		total_bytes_read += bytes_read;
// 		bytes_read = read_file(fd, &line_buffer, buffer);
// 		if (bytes_read == -1)
// 			return (NULL);
// 		new_line_pos = ft_strchr(line_buffer + total_bytes_read, '\n');
// 	}
// 	return ((free(buffer)), get_result(&line_buffer, new_line_pos));
// }

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
