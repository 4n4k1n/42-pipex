/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:34 by apregitz          #+#    #+#             */
/*   Updated: 2025/04/28 14:11:52 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// function to process the child

void	child(char **av, char **ev, int *fds)
{
	int	input;

	input = open(av[1], O_RDONLY, 0777);
	if (input == -1)
		error("open");
	dup2(fds[1], 1);
	dup2(input, 0);
	close(fds[0]);
}

// function to process the parent

void	parent(char **av, char **ev, int *fds)
{
	int	output;

	output = open(av[1], O_WRONLY, 0777);
	if (output == -1)
		error("open");
	dup2(fds[1], 0);
	dup2(output, 1);
	close(fds[1]);
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
