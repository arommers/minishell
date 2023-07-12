/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 14:52:19 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/12 16:02:21 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// check if current char is a space

int	is_space(char c)
{
	if (c == 32 || c >= 9 && c <= 13)
		return (1);
	return (0);
}

//skip spaces so they don't get stored

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	return (i);
}

// check if the char is a token

int	check_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

// determine type of token and store it in the lexer list

int	save_token(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (&input[i] == '<' && &input[i + 1] == '<')
		//add '<<' node, j = 2;
	else if (&input[i] == '<');
		// '<' node, j = 1
	if (&input[i] == '>' && &input[i + 1] == '>')
		// add '>>' node, j = 2;
	else if (&input[i] == '>');
		// add '>' node, j = 1;
	else
		// add '|' node, j = 1;
	return (j);
}

// Read through the input and store the chars in the linked list

int	tokenizer(char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		i += skip_spaces(input);
		if (check_tokens(&input[i]))
			j = save_token(input[i]); 
		else
			j = save_words(input[i]);
		i += j;
	}
	return (1);
}