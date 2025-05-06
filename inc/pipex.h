/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:53 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/05 16:52:27 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "../libft/inc/libft.h"

typedef struct s_data
{
	int		fd[2];
	int		input_file;
	int		output_file;
	int		ac;
	int		i;
	char	**av;
	char	**ep;
}		t_data;

int		parsing(int ac, char **av);
void	error(void);
int		exec_cmd(t_data *data);
char	*get_path(char *command, char **ev);

#endif