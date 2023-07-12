/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 13:57:54 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/12 15:19:15 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	char	*input;

	input = readline(PROMPT);
	while (input != NULL)
	{
		printf("You entered: %s\n", input);
		add_history(input);
		free(input);
		input = readline(PROMPT);
	}
	return (0);
}

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
		if (check_tokens(input[i]))
			j = save_token(input[i]); 
		else
			j = save_words(input[i]);
		i += j;
	}
	return (1);
}
