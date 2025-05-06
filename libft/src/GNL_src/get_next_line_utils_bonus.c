/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:21:05 by apregitz          #+#    #+#             */
/*   Updated: 2025/03/21 15:13:41 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*arr;

	if (!count || !size)
		return (malloc(1));
	if (size != 0 && count > ~(size_t)0 / size)
		return (NULL);
	arr = malloc(count * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < (size * count))
	{
		((unsigned char *)arr)[i] = 0;
		i++;
	}
	return (arr);
}

int	ft_strclen(const char *str, int ch)
{
	int	i;

	if (!str)
		return (NOT_FOUND);
	if (ch == -1)
		ch = '\0';
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)ch)
			return (i);
		i++;
	}
	if (str[i] == ch)
		return (i);
	return (NOT_FOUND);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*arr;
	int		i;

	if (!s1 || !s2)
		return (free((void *)s1), free((void *)s2), NULL);
	len_s1 = ft_strclen(s1, 0);
	len_s2 = ft_strclen(s2, 0);
	arr = (char *)ft_calloc(len_s1 + len_s2 + 1, 1);
	if (!arr)
		return (free((void *)s1), free((void *)s2), NULL);
	i = -1;
	while (++i < len_s1 + len_s2)
	{
		if (i < len_s1)
			arr[i] = s1[i];
		else
			arr[i] = s2[i - len_s1];
	}
	free((void *)s1);
	free((void *)s2);
	return (arr);
}

char	*ft_strdup(const char *string, char ch)
{
	int		len;
	int		i;
	char	*new_arr;

	if (!string || !*string)
		return (ft_calloc(1, 1));
	len = 0;
	while (string[len] && string[len] != ch)
		len++;
	if (ch != '\0' && string[len] == ch)
		len++;
	new_arr = (char *)ft_calloc(len + 1, 1);
	if (!new_arr)
		return (NULL);
	i = -1;
	while (++i < len)
		new_arr[i] = string[i];
	return (new_arr);
}

void	*ft_check_str(char *str)
{
	if (!(*str))
		return (free((void *)str), NULL);
	return (str);
}
