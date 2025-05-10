/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:53 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/10 12:48:14 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
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
}			t_data;

// utils
void	error(void);
void	free_2d_array(char **arr);

// parsing
int		parsing(int ac);

// here_doc
void	here_doc(t_data *data, char *lim);

// building / prepareing the child
void	build_child(t_data *data, int last);

// init struct and open files
int		init_struct(t_data *data, int ac, char **av, char **ep);

#endif