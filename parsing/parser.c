/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 15:18:45 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/20 15:52:51 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_nodes(t_lexer *head, t_tokens token)
{
	t_lexer	*current;
	int		i;

	i = 0;
	current = head;
	while (current && current->token != PIPE)
	{
		current = current->next;
		i++;
	}
	return (i);
}

int	group_tokens(t_lexer *head)
{
	t_lexer	*current;
	int		i;

	i = count_nodes(head, PIPE);
	current = head;
}

int	parser(t_data *data)
{
	group_tokens(data->lexer);
	return (1);
}
