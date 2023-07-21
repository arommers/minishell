/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_del.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 12:43:31 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/21 14:53:08 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lexer(t_lexer **head)
{
	t_lexer	*tmp;
	t_lexer	*current;

	current = *head;
	while (current)
	{
		tmp = current;
		if (current->chars)
			free(current->chars);
		current = current->next;
		free (tmp);
	}
	head = NULL;
}

// Delete a node with a matching value from the list

void	del_lex_node(t_lexer **head, int match)
{
	t_lexer	*current;
	t_lexer	*tmp;

	current = *head;
	if (current && current->index == match)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*head = current;
	while (current->next && current->next->index != match)
		current = current->next;
	if (current->next)
	{
		tmp = current->next;
		current->next = current->next->next;
		free(tmp);
	}
}
