/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:13:12 by apregitz          #+#    #+#             */
/*   Updated: 2025/04/28 15:01:01 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	error(char *msg)
{
	perror(msg);
	exit(1);
}

int	process(char *av, char **ev)
{
	char	**command;
	char	*path;
	int		i;

	return (1);
}
