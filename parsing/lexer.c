/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 14:52:19 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/26 16:05:42 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// check if the passed argument is a token and determine which

t_tokens	check_index(char *input, int i)
{
	if (input[i] == '|')
		return (PIPE);
	else if (input[i] == '<')
	{
		if (i + 1 < (int)strlen(input) && input[i + 1] == '<')
			return (LESSLESS);
		else
			return (LESS);
	}
	else if (input[i] == '>')
	{
		if (i + 1 < (int)strlen(input) && input[i + 1] == '>')
			return (GREATGREAT);
		else
			return (GREAT);
	}
	return (WORDS);
}

// determine type of token and store it in the lexer list

int	store_token(t_data *data, int i)
{
	t_tokens	token;
	int			j;

	token = check_index(data->input, i);
	if (token == LESSLESS || token == GREATGREAT)
	{
		if (add_lex_node(&data->lexer, token, NULL) != 1)
			return (-1);
		j = 2;
	}
	else
	{
		if (add_lex_node(&data->lexer, token, NULL) != 1)
			return (-1);
		j = 1;
	}
	return (j);
}

// Iterates throught the input string until it reaches a delimiter
// or the end of the line and stores the string in a node

int	store_words(t_data *data, int i)
{
	int		j;

	j = 0;
	while (data->input[i + j] && !check_index(data->input, i + j))
	{
		if (check_quotes(data->input[i + j]))
		{
			j += store_quoted(data->input, i + j + 1, data->input[i + j]);
		}
		if (is_space(data->input[i + j]) || !data->input[i + j])
			break ;
		if (data->input[i + j])
			j++;
	}
	if (add_lex_node(&data->lexer, 0, ft_substr(data->input, i, j)) != 1)
		return (-1);
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
		i += skip_spaces(data->input, i);
		if (check_index(data->input, i))
			j = store_token(data, i); 
		else
			j = store_words(data, i);
		if (j < 0)
			return (0);
		i += j;
	}
	print_lex_list(data->lexer);
	parser(data);
	return (1);
}
