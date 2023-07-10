/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 13:57:54 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/10 14:07:21 by arommers      ########   odam.nl         */
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
