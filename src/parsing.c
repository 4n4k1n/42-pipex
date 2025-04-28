/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:07:49 by apregitz          #+#    #+#             */
/*   Updated: 2025/04/28 14:26:33 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	parsing(int ac, char **av)
{
	if (ac == 5 && av)
		return (1);
	write(1, "Invalid arguments!\n", 19);
	write(1, "./pipex <file1> <cmd1> <cmd2> <file2>\n", 38);
	return (1);
}
