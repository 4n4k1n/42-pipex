/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:34 by apregitz          #+#    #+#             */
/*   Updated: 2025/04/28 12:47:30 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child(char **av, char **ev, int *fds)
{
	int	input;
}

void	parent(char **av, char **ev, int *fds)
{
	int	output;

	output = open(av[1], O_RDONLY, 0777);
	if (output == -1)
		error("open");
}

int	main(int ac, char **av, char **ev)
{
	pid_t	pid;
	int		fds[2];

	if (!parsing(ac, av))
		return (1);
	if (pipe(fds) == -1)
		perror("pipe");
	pid = fork();
	if (pid == 0)
	{

	}
	else
	return (0);
}
