/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_util.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 12:00:21 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/28 12:41:55 by arommers      ########   odam.nl         */
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

// Check if the character at the current index is a single or double quote

int	check_quotes(char q)
{
	if (q == '\'' || q == '\"')
		return (1);
	return (0);
}

// Iterate until matching quote or the end of the string is found

int	store_quoted(char *input, int i, char q)
{
	int	j;

	j = 0;
	if (!input[i])
		return (1);
	while (input[i + j] && input[i + j] != q)
		j++;
	if (!input[i + j])
		return (j);
	else
		return (j + 1);
}

// Checks if the last node in the linked list contains a pipe

int	check_last(t_lexer **head)
{
	t_lexer	*current;

	current = *head;
	while (current)
	{
		if (current->token == PIPE)
			return (1);
		current = current->next;
	}
	return (0);
}
