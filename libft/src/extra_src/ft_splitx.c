/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hntest2 <hntest2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 10:15:32 by anakin            #+#    #+#             */
/*   Updated: 2025/05/25 11:11:20 by hntest2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	count_args_loop(const char *s, t_arg_data *data)
{
	while (s[data->pos])
	{
		if (data->esc)
			data->esc = 0;
		else if (s[data->pos] == '\\' && !data->in_s_quote)
			data->esc = 1;
		else if (s[data->pos] == '\'' && !data->in_d_quote)
			data->in_s_quote = !data->in_s_quote;
		else if (s[data->pos] == '"' && !data->in_s_quote)
			data->in_d_quote = !data->in_d_quote;
		else if (!data->in_s_quote && !data->in_d_quote \
			&& is_whitespacex(s[data->pos]))
		{
			if (data->in_word)
			{
				data->in_word = 0;
				data->arg_count++;
			}
		}
		else if (!data->in_word)
			data->in_word = 1;
		data->pos++;
	}
}

static int	count_args(const char *s)
{
	t_arg_data	data;

	ft_memset(&data, 0, sizeof(t_arg_data));
	data.arg_count = 0;
	data.in_word = 0;
	count_args_loop(s, &data);
	if (data.in_word)
		data.arg_count++;
	return (data.arg_count);
}

static int	extract_arg_loop_checks(const char *s, t_arg_data *data)
{
	if (data->esc)
	{
		if (s[data->pos] == 'n')
			data->arg[data->write_pos++] = '\n';
		else if (s[data->pos] == 't')
			data->arg[data->write_pos++] = '\t';
		else if (s[data->pos] == 'r')
			data->arg[data->write_pos++] = '\r';
		else
			data->arg[data->write_pos++] = s[data->pos];
		data->esc = 0;
	}
	else if (s[data->pos] == '\\' && !data->in_s_quote)
		data->esc = 1;
	else if (s[data->pos] == '\'' && !data->in_d_quote)
		data->in_s_quote = !data->in_s_quote;
	else if (s[data->pos] == '"' && !data->in_s_quote)
		data->in_d_quote = !data->in_d_quote;
	else if (!data->in_s_quote && !data->in_d_quote \
		&& is_whitespacex(s[data->pos]))
		return (0);
	else
		data->arg[data->write_pos++] = s[data->pos];
	data->pos++;
	return (1);
}

static char	*extract_arg(const char *s, int start, int *end_pos)
{
	t_arg_data	data;
	char		*arg_ptr;

	data.arg_len = calc_arg_lengthx(s, start);
	arg_ptr = (char *)malloc(sizeof(char) * (data.arg_len + 1));
	if (!arg_ptr)
		return (NULL);
	ft_memset(&data, 0, sizeof(t_arg_data));
	data.arg = arg_ptr;
	data.pos = start;
	data.write_pos = 0;
	while (s[data.pos] && extract_arg_loop_checks(s, &data))
		;
	data.arg[data.write_pos] = '\0';
	*end_pos = data.pos;
	return (data.arg);
}

char	**ft_splitx(const char *s)
{
	t_splitx_main_data	data;

	if (!s)
		return (NULL);
	data.arg_count = count_args(s);
	data.result = (char **)malloc(sizeof(char *) * (data.arg_count + 1));
	if (!data.result)
		return (NULL);
	data.current_arg = 0;
	data.pos = skip_whitespacex(s, 0);
	while (data.current_arg < data.arg_count && s[data.pos])
	{
		data.result[data.current_arg] = \
		extract_arg(s, data.pos, &data.next_pos);
		if (!data.result[data.current_arg])
			return (ft_free_splitx(data.result, data.current_arg), NULL);
		data.current_arg++;
		data.pos = skip_whitespacex(s, data.next_pos);
	}
	data.result[data.arg_count] = NULL;
	return (data.result);
}

// #include <stdio.h>
// int main(void)
// {
// 	char *test_cases[] = {
// 		"ls -la",
// 		"echo \"hello world\"",
// 		"echo 'single quotes'",
// 		"grep \"pattern with spaces\" file.txt",
// 		"echo \"nested \\\"quotes\\\"\"",
// 		"echo 'don\\'t escape in single quotes'",
// 		"command arg1 \"arg with spaces\" 'another arg'",
// 		"echo \"line1\\nline2\\ttab\"",
// 		NULL
// 	};
// 	for (int i = 0; test_cases[i]; i++)
// 	{
// 		printf("Input: %s\n", test_cases[i]);
// 		char **args = ft_shell_split(test_cases[i]);
// 		if (args)
// 		{
// 			for (int j = 0; args[j]; j++)
// 			{
// 				printf("  [%d]: '%s'\n", j, args[j]);
// 			}
// 			ft_free_split(args, -1);
// 		}
// 		else
// 		{
// 			printf("  Failed to parse\n");
// 		}
// 		printf("\n");
// 	}
// 	return (0);
// }
