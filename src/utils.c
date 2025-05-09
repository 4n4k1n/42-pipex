/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:13:12 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/09 21:44:24 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_2d_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

char	*get_path(char *command, char **ev)
{
	int		i;
	char	**bin_paths;
	char	*final_path;
	char	*temp;

	i = 0;
	while (!ft_strnstr(ev[i], "PATH=", 5))
		i++;
	bin_paths = ft_split(ev[i], ':');
	i = -1;
	while (bin_paths[++i])
	{
		temp = ft_strjoin(bin_paths[i], "/");
		final_path = ft_strjoin(temp, command);
		free(temp);
		if (access(final_path, F_OK) == 0)
			return (free_2d_array(bin_paths), final_path);
		free(final_path);
	}
	free_2d_array(bin_paths);
	exit(127);
}

void	in_child_process(t_data *data, char *path, char **cmd)
{
	if (dup2(data->fd[0], STDIN_FILENO) == -1 \
	|| dup2(data->fd[1], STDOUT_FILENO) == -1)
		error();
	close(data->fd[0]);
	close(data->fd[1]);
	execve(path, cmd, data->ep);
	error();
}

int	exec_cmd(t_data *data)
{
	char	**command;
	char	*path;
	pid_t	pid;
	int		status;

	command = ft_split(data->av[data->i], ' ');
	path = get_path(*command, data->ep);
	if (!path)
		return (free_2d_array(command), error(), 0);
	pid = fork();
	if (pid == 0)
		in_child_process(data, path, command);
	waitpid(pid, &status, 0);
	free(path);
	free_2d_array(command);
	return (1);
}
