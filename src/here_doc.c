/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:13:39 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/09 20:29:09 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	here_doc(t_data *data, char *lim)
{
	int		len;
	char	*str;
	int		fd[2];

	data->i++;
	len = ft_strlen(lim);
	if (pipe(fd) == -1)
		error();
	while (1)
	{
		write(fd[1], "heredoc>", 8);
		str = get_next_line(0);
		if (!str)
			return (close(data->fd[0]), close(data->fd[0]), error());
		if (ft_strncmp(lim, str, len) == 0 && str[len] == '\n')
		{
			free(str);
			break;
		}
		write(fd[1], str, ft_strlen(str));
		free(str);
	}
	close(fd[1]);
	data->fd[0] = fd[0];
}
