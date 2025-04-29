/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:34 by apregitz          #+#    #+#             */
/*   Updated: 2025/04/29 16:34:02 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// function to process the child

void	child(char **av, char **ev, int *fds)
{
	int	input;
	int	flags;

	flags = O_RDONLY;
	input = open(av[1], flags, 0777);
	if (input == -1)
		error("open");
	dup2(input, STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
	close(input);
	process(av[2], ev);
}

// function to process the parent

void	parent(char **av, char **ev, int *fds)
{
	int		output;
	int		flags;

	flags = O_WRONLY | O_TRUNC | O_CREAT;
	output = open(av[4], flags , 0644);
	if (output == -1)
		error("open");
	dup2(fds[0], STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
	close(output);
	process(av[3], ev);
}

int	main(int ac, char **av, char **ev)
{
	pid_t	pid;
	int		fds[2];
	int		status;

	(void)ac;
	if (!parsing(ac, av))
		return (1);
	if (pipe(fds) == -1)
	{
		printf("im here 1\n");
		perror("pipe");
	}
	pid = fork();
	if (pid == 0)
		child(av, ev, fds);
	else
		parent(av, ev, fds);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		printf("Main Child exit: %d\n", WEXITSTATUS(status));
	return (0);
}
