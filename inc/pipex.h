/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:53 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/07 20:11:26 by apregitz         ###   ########.fr       */
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

# ifndef BONUS
#  define BONUS 0
# endif

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

int		parsing(int ac);
void	error(void);
int		exec_cmd(t_data *data);
char	*get_path(char *command, char **ev);
void	here_doc(t_data *data, char *lim);

#endif