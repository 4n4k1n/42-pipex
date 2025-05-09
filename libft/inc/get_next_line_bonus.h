/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:54:28 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/07 20:15:11 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# define NOT_FOUND -1

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

char	*ft_read_file_until_newline(int fd, char *buffer, int *read_error);
char	*get_next_line(int fd);

char	*ft_strjoin_gnl(const char *s1, const char *s2);
int		ft_strclen_gnl(const char *str, int ch);
void	*ft_calloc_gnl(size_t count, size_t size);
char	*ft_strdup_gnl(const char *string, char ch);
void	*ft_check_str_gnl(char *str);

#endif
