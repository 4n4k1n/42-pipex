/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:13:12 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/01 00:24:06 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	check_absulut_path(char *path)
{
	if (access(path, F_OK) == 0)
		return (1);
	return (0);
}

void	free_2d_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr[i]);
	free(arr);
}

void	error(char *msg)
{
	perror(msg);
	exit(1);
}

char	*get_path(char *command, char **ev)
{
	int		i;
	char	**bin_paths;
	char	*final_path;
	char	*temp;

	i = 0;
	while (!ft_strnstr(ev[i], "PATH", 4))
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
	return (free_2d_array(bin_paths), NULL);
}

int	process(char *av, char **ev, pid_t pid)
{
	char	**command;
	char	*path;
	int		status;

	command = ft_split(av, ' ');
	if (check_absulut_path(*command))
		path = *command;
	else
	{
		path = get_path(*command, ev);
		if (!path)
			return (free_2d_array(command), error("error"), 0);
	}
	if (pid == 0)
	{
		execve(path, command, ev);
		error("execve");
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit (WEXITSTATUS (status));
	return (1);
}
