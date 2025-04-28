/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:13:12 by apregitz          #+#    #+#             */
/*   Updated: 2025/04/28 16:50:12 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	error(char *msg)
{
	perror(msg);
	exit(1);
}

char *get_path(char *command, char *ev);

int	process(char *av, char **ev)
{
	char	**command;
	char	*path;
	int		i;

	while (ev[i] && !ft_strnstr(ev[i], "PATH", 4))
		i++;
	if (!ev)
		return (0);
	command = ft_split(av[i], ' ');
	if (!command)
		return (0);
	return (1);
}
