/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:07:49 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/09 20:36:48 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	parsing(int ac)
{
	if (BONUS)
	{
		if (ac >= 5)
			return (1);
		write(1, "Invalid arguments!\n", 19);
		write(1, "./pipex <file1> <cmd1> <cmd2> ... <file2>\n", 42);
	}
	else
	{
		if (ac == 5)
			return (1);
		write(1, "Invalid arguments!\n", 19);
		write(1, "./pipex <file1> <cmd1> <cmd2> <file2>\n", 38);
	}
	return (0);
}
