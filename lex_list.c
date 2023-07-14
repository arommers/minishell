/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 16:03:16 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/14 15:07:57 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// one function to add nodes

//one function to allocate and make a new node

// function to add the new node to the linked list

//function prototype: int	add_node (t_lexer **list, t_tokens token, char *chars)

#include "includes/minishell.h"

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

// function to add nodes.
// Return value should

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
