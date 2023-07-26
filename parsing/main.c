/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 13:57:54 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/26 16:06:13 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_data	data;

	data.input = readline(PROMPT);
	data.lexer = NULL;
	data.cmds = NULL;
	while (data.input != NULL)
	{
		tokenizer(&data);
		parser(&data);
		add_history(data.input);
		free_lexer(&data.lexer);
		free(data.input);
		data.input = readline(PROMPT);
	}
	return (0);
}
