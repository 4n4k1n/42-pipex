/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:24:52 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/10 12:37:46 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static int	open_files(t_data *data)
{
	int	hd_flags;
	int	flags;

	hd_flags = O_WRONLY | O_CREAT | O_APPEND;
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (BONUS && ft_strncmp(data->av[1], "here_doc", 9) == 0)
	{
		data->output_file = open(data->av[data->ac - 1], hd_flags, 0777);
		if (data->output_file == -1)
			error();
	}
	else
	{
		data->input_file = open(data->av[1], O_RDONLY, 0777);
		if (data->input_file == -1)
			error();
		data->fd[0] = data->input_file;
		data->output_file = open(data->av[data->ac - 1], flags, 0777);
		if (data->output_file == -1)
			return (close(data->input_file), 0);
	}
	data->fd[0] = data->input_file;
	return (1);
}

int	init_struct(t_data *data, int ac, char **av, char **ep)
{
	data->fd[0] = data->input_file;
	data->ac = ac;
	data->ep = ep;
	data->av = av;
	data->i = 1;
	open_files(data);
	return (1);
}
