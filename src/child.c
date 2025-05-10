/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:31:33 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/10 12:32:21 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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

	command = ft_split(data->av[data->i], ' ');
	path = get_path(*command, data->ep);
	if (!path)
		return (free_2d_array(command), error(), 0);
	pid = fork();
	if (pid == 0)
		in_child_process(data, path, command);
	free(path);
	free_2d_array(command);
	return (1);
}

void	build_child(t_data *data, int last)
{
	int	fd[2];

	if (!last && pipe(fd) == -1)
		error();
	if (last)
		data->fd[1] = data->output_file;
	else
		data->fd[1] = fd[1];
	exec_cmd(data);
	if (last)
		close(data->fd[1]);
	else
	{
		close(fd[1]);
		close(data->fd[0]);
		data->fd[0] = fd[0];
	}
}
