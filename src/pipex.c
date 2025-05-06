/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:34 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/06 11:08:10 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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

int	init_struct(t_data *data, int ac, char **av, char **ep)
{
	data->input_file = open(av[1], O_RDONLY, 0777);
	if (data->input_file == -1)
		return (0);
	data->output_file = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->output_file == -1)
		return (close(data->input_file), 0);
	data->fd[0] = data->input_file;
	data->ac = ac;
	data->ep = ep;
	data->av = av;
	data->i = 1;
	return (1);
}

int	main(int ac, char **av, char **ep)
{
	t_data	data;

	if (!parsing(ac, av))
		return (1);
	if (!init_struct(&data, ac, av, ep))
		return (1);
	while (++(data.i) < ac - 2)
		build_child(&data, 0);
	build_child(&data, 1);
	return (0);
}
