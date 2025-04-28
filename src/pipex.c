/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:34 by apregitz          #+#    #+#             */
/*   Updated: 2025/04/28 23:51:30 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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
	process(av[2], ev);
}

// function to process the parent

void	parent(char **av, char **ev, int *fds)
{
	int	output;

	output = open(av[4], O_WRONLY, 0777);
	if (output == -1)
		error("open");
	dup2(fds[1], 0);
	dup2(output, 1);
	write(1, "this is a test", 14);
	process(av[3], ev);
	close(fds[1]);
}

int	main(int ac, char **av, char **ev)
{
	pid_t	pid;
	int		fds[2];

	(void)ac;
	if (!parsing(ac, av))
		return (1);
	if (pipe(fds) == -1)
		perror("pipe");
	pid = fork();
	if (pid == 0)
		child(av, ev, fds);
	waitpid(pid, NULL, 0);
	parent(av, ev, fds);
	return (0);
}
