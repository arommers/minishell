/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 14:52:19 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/16 13:24:51 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// check if current char is a white space

int	is_space(char c)
{
	if (c == 32 || c > 8 && c < 14)
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

int	store_token(t_data *data, int i)
{
	int	token;
	int	j;

	token = check_index(data->input, i);
	if (token == LESSLESS || token == GREATGREAT)
	{
		if (add_node(&data->lexer, (t_tokens)token, NULL) != 1)
			return (-1);
		j = 2;
	}
	else
	{
		if (add_node(&data->lexer, (t_tokens)token, NULL) != 1)
			return (-1);
		j = 1;
	}
	return (j);
}

// Read through the input and devide into tokens in the lexer linked list

int	tokenizer(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->input[i])
	{
		j = 0;
		i += skip_spaces(data->input);
		if (check_index(data->input, i))
			j = store_token(data, i); 
		else
			j = store_words(data->input);
		i += j;
	}
	return (1);
}
