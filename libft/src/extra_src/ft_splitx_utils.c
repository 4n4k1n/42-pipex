/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitx_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hntest2 <hntest2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 08:27:20 by anakin            #+#    #+#             */
/*   Updated: 2025/05/25 11:12:00 by hntest2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_splitx(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	is_whitespacex(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	skip_whitespacex(const char *s, int pos)
{
	while (s[pos] && is_whitespacex(s[pos]))
		pos++;
	return (pos);
}

int	calc_arg_lengthx(const char *s, int start)
{
	t_arg_data	data;

	ft_memset(&data, 0, sizeof(t_arg_data));
	data.pos = start - 1;
	data.arg_len = 0;
	while (s[++data.pos])
	{
		if (data.esc)
		{
			data.arg_len++;
			data.esc = 0;
		}
		else if (s[data.pos] == '\\' && !data.in_s_quote)
			data.esc = 1;
		else if (s[data.pos] == '\'' && !data.in_d_quote)
			data.in_s_quote = !data.in_s_quote;
		else if (s[data.pos] == '"' && !data.in_s_quote)
			data.in_d_quote = !data.in_d_quote;
		else if (!data.in_s_quote && !data.in_d_quote \
			&& is_whitespacex(s[data.pos]))
			break ;
		else
			data.arg_len++;
	}
	return (data.arg_len);
}
