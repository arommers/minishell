/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_util.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 12:00:21 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/17 14:45:23 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// check if current char is a white space

int	is_space(char c)
{
	if (c == 32 || (c > 8 && c < 14))
		return (1);
	return (0);
}

//skip white spaces so they don't get stored

int	skip_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while (is_space(str[i + j]))
		j++;
	return (j);
}

int	check_quotes(char *input, int i, char q)
{
	int	j;

	j = 0;
	while (input[i + j])
	{
		
	}
	return (j);
}