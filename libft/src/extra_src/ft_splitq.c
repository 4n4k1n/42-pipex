/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:26:58 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/11 18:33:49 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"

static void	ft_free_split(char **arr, int count)
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

static int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

static int	count_words_quoted(char const *s, char c)
{
	int		count;
	int		active;
	char	quote_type;
	int		i;
	int		escaped;

	active = 0;
	count = 0;
	quote_type = 0;
	i = 0;
	escaped = 0;
	while (s[i])
	{
		if (s[i] == '\\' && !escaped)
		{
			escaped = 1;
			i++;
			continue ;
		}
		if (is_quote(s[i]) && !escaped)
		{
			if (quote_type == 0)
				quote_type = s[i];
			else if (quote_type == s[i])
				quote_type = 0;
		}
		if (!quote_type)
		{
			if (!active && s[i] != c)
			{
				active = 1;
				count++;
			}
			else if (active && s[i] == c)
				active = 0;
		}
		escaped = 0;
		i++;
	}
	return (count);
}

static const char *get_word_index_quoted(const char *s, char c)
{
	char quote_type;
	int escaped;

	quote_type = 0;
	escaped = 0;
	while (*s)
	{
		if (*s == '\\' && !escaped)
		{
			escaped = 1;
			s++;
			continue;
		}
		if (is_quote(*s) && !escaped)
		{
			if (quote_type == 0)
				quote_type = *s;
			else if (quote_type == *s)
				quote_type = 0;
		}
		if (*s == c && !quote_type)
			s++;
		else
			return (s);
		escaped = 0;
	}
	return (s);
}

static char *alloc_word_quoted(const char **s, char c)
{
	int     i;
	int     j;
	char    quote_type;
	char    *arr;
	int     escaped;
	int     len;

	i = 0;
	len = 0;
	quote_type = 0;
	escaped = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '\\' && !escaped)
		{
			escaped = 1;
			i++;
			continue;
		}
		if (is_quote((*s)[i]) && !escaped)
		{
			if (quote_type == 0)
				quote_type = (*s)[i];
			else if (quote_type == (*s)[i])
				quote_type = 0;
		}
		if ((*s)[i] == c && !quote_type)
			break;
		len++;
		escaped = 0;
		i++;
	}
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	quote_type = 0;
	escaped = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '\\' && !escaped)
		{
			escaped = 1;
			i++;
			continue;
		}
		if (is_quote((*s)[i]) && !escaped)
		{
			if (quote_type == 0)
				quote_type = (*s)[i];
			else if (quote_type == (*s)[i])
				quote_type = 0;
		}
		if ((*s)[i] == c && !quote_type)
			break;
		arr[j++] = (*s)[i];
		escaped = 0;
		i++;
	}
	arr[j] = '\0';
	*s += i;
	return (arr);
}

char **ft_splitq(char const *s, char c)
{
	char	**arr;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	words = count_words_quoted(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < words)
	{
		s = get_word_index_quoted(s, c);
		arr[i] = alloc_word_quoted(&s, c);
		if (!arr[i])
			return (ft_free_split(arr, i), NULL);
		i++;
	}
	arr[words] = NULL;
	return (arr);
}

// int main(int ac, char **av)
// {
// 	if (ac != 2)
// 		return (1);
// 	char **arr = ft_split_quoted(av[1], ' ');
// 	int i = -1;
	
// 	for (int i = 0; arr[i]; i++)
// 		printf("%s ", arr[i]);
// 	while (arr[++i])
// 		free(arr[i]);
// 	free(arr[i]);
// 	free(arr);
// 	return (0);
// }
