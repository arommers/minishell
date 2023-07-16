/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 14:52:19 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/16 11:35:14 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// check if current char is a white space

int	is_space(char c)
{
	if (c == 32 || c >= 9 && c <= 13)
		return (1);
	return (0);
}

//skip white spaces so they don't get stored

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	return (i);
}

// check if and which token passed argument is

int	check_index(char *input, int i)
{
	if (input[i] == '|')
		return (PIPE);
	else if (input[i] == '<')
	{
		if (i + 1 < ft_strlen(input) && input[i + 1] == '<')
			return (LESSLESS);
		else
			return (LESS);
	}
	else if (input[i] == '>')
	{
		if (i + 1 < ft_strlen(input) && input[i + 1] == '>')
			return (GREATGREAT);
		else
			return (GREAT);
	}
	return (WORDS);
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
	else if (&input[i] == '>' && &input[i + 1] == '>')
		// add '>>' node, j = 2;
	else if (&input[i] == '>');
		// add '>' node, j = 1;
	else
		// add '|' node, j = 1;
	return (j);
}

// Read through the input and devide into tokens in the linked list

int	tokenizer(char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		i += skip_spaces(input);
		if (check_index(input, i))
			j = save_token(input); 
		else
			j = save_words(input);
		i += j;
	}
	return (1);
}
