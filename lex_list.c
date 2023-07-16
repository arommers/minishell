/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 16:03:16 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/16 11:08:43 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Create a new node for the lexer list

t_lexer	*make_node(t_lexer *new, t_tokens token, char *chars)
{
	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->chars = chars;
	new->token = token;
	// new->len = len;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

// Creates a new node and adds it to the back of the doubly linked list

int	add_node(t_lexer **head, t_tokens token, char *chars)
{
	t_lexer	*new;
	t_lexer	*current;

	new = make_node(new, token, chars);
	if (!new)
		return (0);
	if (!*head)
	{
		*head = new;
		return (1);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	new->next = NULL;
	return (1);
}
