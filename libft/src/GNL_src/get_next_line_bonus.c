/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:13:40 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/09 23:32:21 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_remove_garbage(char *buffer)
{
	int	i;
	int	check;

	check = ft_strclen_gnl(buffer, '\n');
	if (check == NOT_FOUND)
	{
		buffer[0] = '\0';
		return ;
	}
	i = -1;
	while (buffer[++i + check + 1])
		buffer[i] = buffer[i + check + 1];
	buffer[i] = '\0';
}

char	*ft_check_buffer(char *buffer)
{
	int	check;

	if (!buffer[0])
		return (ft_calloc_gnl(1, 1));
	check = ft_strclen_gnl(buffer, '\n');
	if (check != NOT_FOUND)
		return (ft_strdup_gnl(buffer, '\n'));
	return (ft_strdup_gnl(buffer, '\0'));
}

int	ft_read_in_buffer(int fd, char *buffer, int *active)
{
	int	check;

	check = read(fd, buffer, BUFFER_SIZE);
	if (check != BUFFER_SIZE)
		*active = 0;
	if (check >= 0)
		buffer[check] = '\0';
	else
		buffer[0] = '\0';
	return (check);
}

char	*ft_read_line(int fd, char *buffer)
{
	char	*str;
	char	*temp;
	int		active;
	int		read_result;

	active = 1;
	str = ft_check_buffer(buffer);
	if (!str)
		return (NULL);
	while (ft_strclen_gnl(str, '\n') == NOT_FOUND && active)
	{
		read_result = ft_read_in_buffer(fd, buffer, &active);
		if (read_result == -1)
			return (free(str), NULL);
		if (read_result == 0 && !*str)
			return (free(str), NULL);
		temp = ft_check_buffer(buffer);
		if (!temp)
			return (free(str), NULL);
		str = ft_strjoin_gnl(str, temp);
		if (!str)
			return (NULL);
	}
	ft_remove_garbage(buffer);
	return (ft_check_str_gnl(str));
}

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1] = {0};
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read_line(fd, buffer[fd]);
	return (str);
}
