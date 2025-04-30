/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:34 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/01 00:23:47 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// function to process the child

void	child(char **av, char **ev, int *fds, pid_t pid)
{
	int	input;

	input = open(av[1], O_RDONLY, 0777);
	if (input == -1)
		error("open");
	dup2(input, STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
	close(input);
	process(av[2], ev, pid);
}

// function to process the parent

void	parent(char **av, char **ev, int *fds, pid_t pid)
{
	int	output;

	output = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (output == -1)
		error("open");
	dup2(fds[0], STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
	close(output);
	process(av[3], ev, pid);
}

void	open_pids(pid_t *pid1, pid_t *pid2)
{
	*pid1 = fork();
	if (*pid1 != 0)
		*pid2 = fork();
}

void	close_pids(pid_t *pid1, pid_t *pid2)
{
	int	status;

	waitpid(*pid1, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	waitpid(*pid2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

int	main(int ac, char **av, char **ev)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fds[2];

	(void)ac;
	if (!parsing(ac, av))
		return (1);
	if (pipe(fds) == -1)
		perror("pipe");
	open_pids(&pid1, &pid2);
	if (pid1 == 0)
		child(av, ev, fds, pid1);
	if (pid2 == 0)
		parent(av, ev, fds, pid2);
	close_pids(&pid1, &pid2);
	return (0);
}
