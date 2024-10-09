/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 23:10:16 by eebert            #+#    #+#             */
/*   Updated: 2024/10/09 10:21:17 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

typedef struct s_list
{
	char			*buffer;
	size_t			buffer_size;
	struct s_list	*next;
}					t_list;

void				ft_lstadd_back(t_list **lst, t_list *new);

char				*get_next_line(int fd);

char				*ft_strchr(const char *str, int c);

char				*ft_strjoin(char const *s1, char const *s2);

int					ft_strlen(const char *s);

char				*ft_strndup(const char *src, size_t n);

#endif