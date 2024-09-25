/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 23:10:16 by eebert            #+#    #+#             */
/*   Updated: 2024/09/25 23:30:27 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>

# ifndef MAX_FILES_OPENED
#  define MAX_FILES_OPENED 65536
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

char	*ft_strchr(const char *str, int c);

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strlen(const char *s);

char	*ft_strndup(const char *src, size_t n);

#endif