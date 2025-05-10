/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:34 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/10 12:35:00 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int ac, char **av, char **ep)
{
	t_data	data;
	int		exit_code;

	if (!parsing(ac) || !init_struct(&data, ac, av, ep))
		return (1);
	if (BONUS && ft_strncmp(av[1], "here_doc", 9) == 0)
		here_doc(&data, av[2]);
	while (++(data.i) < ac - 2)
		build_child(&data, 0);
	build_child(&data, 1);
	while (wait(&exit_code) > 0)
		;
	if (WIFEXITED(exit_code))
		exit(WEXITSTATUS(exit_code));
	return (0);
}
