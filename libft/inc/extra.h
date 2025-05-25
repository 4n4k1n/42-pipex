/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:19:22 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/25 09:54:12 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRA_H
# define EXTRA_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_arg_data
{
	int		in_s_quote;
	int		in_d_quote;
	int		esc;
	int		start;
	int		pos;
	char	*arg;
	int		arg_len;
	int		write_pos;
	int		arg_count;
	int		in_word;
}			t_arg_data;

typedef struct s_splitx_main_data
{
	char	**result;
	int		arg_count;
	int		current_arg;
	int		pos;
	int		next_pos;
}			t_splitx_main_data;

char		*ft_strrev(char *string);
char		*smash(const char **words, char seperator, size_t count);
int			ft_swp(void *arr1, void *arr2, size_t size);
ssize_t		ft_strclen(const char *str, char ch);
char		**ft_splitx(const char *s);
void		ft_free_splitx(char **arr, int count);
int			is_whitespacex(char c);
int			skip_whitespacex(const char *s, int pos);
int			calc_arg_lengthx(const char *s, int start);

#endif