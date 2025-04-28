/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:13:12 by apregitz          #+#    #+#             */
/*   Updated: 2025/04/28 23:22:37 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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

char *get_path(char *command, char **ev)
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

int	process(char *av, char **ev)
{
	char	**command;
	char	*path;

	command = ft_split(av, ' ');
	path = get_path(*command, ev);
	if (!path)
		return (free_2d_array(command), error("error"), 0);
	if (execve(path, command, ev) == -1)
		error("execve");
	return (1);
}
