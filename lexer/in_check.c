/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   in_check.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 10:46:28 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/10 16:55:33 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_u_quotes(t_data *data)
{
	char	c;
	int		i;

	i = 0;
	while (data->input[i])
	{
		i += skip_spaces(data->input, i);
		if (!data->input[i])
			return ;
		if (data->input[i] == ';' || data->input[i] == '\\')
			quote_error(data, data->input[i]);
		if (check_quotes(data->input[i]))
		{
			c = data->input[i];
			i += store_quoted(data->input, i + 1, c);
			printf("%c\n", data->input[i]);
			if (data->input[i + 1])
				quote_error(data, c);
		}
		else
			i++;
	}
}

/*	Check for any double pipes or ampersands */

void	check_dup(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		i += skip_spaces(data->input, i);
		if (!data->input[i])
			return ;
		if (data->input[i] == '|' && data->input[i + 1] == '|')
			syntax_error(data, PIPE);
		if (data->input[i] == '&' && data->input[i + 1] == '&')
			syntax_error(data, AND);
		i++;
	}
}

void	input_check(t_data *data)
{
	if (!data->input[0])
		reset_data(data);
	check_dup(data);
	check_u_quotes(data);
}
