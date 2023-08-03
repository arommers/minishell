/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pars_util.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 11:36:53 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/30 15:08:26 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Count the number of pipes to determine the number of command nodes needed

void	count_pipes(t_data *data)
{
	t_lexer	*current;

	current = data->lexer;
	while (current)
	{
		if (current->token == PIPE)
			data->nr_pipes++;
		current = current->next;
	}
}

// count the number of arguments that make up one simple command

int	count_args(t_lexer *head)
{
	t_lexer	*current;
	int		i;

	i = 0;
	current = head;
	while (current && current->token != PIPE)
	{
		if (!current->is_token)
			i++;
		current = current->next;
	}
	return (i);
}
