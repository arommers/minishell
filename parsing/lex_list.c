/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 16:03:16 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/27 13:38:28 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create a new node for the lexer list

t_lexer	*make_lex_node(t_lexer *new, t_tokens token, char *str)
{
	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->token = token;
	new->chars = str;
	new->next = NULL;
	return (new);
}

// Creates a new node and adds it to the back of the doubly linked list

int	add_lex_node(t_lexer **head, t_tokens token, char *str)
{
	t_lexer	*new;
	t_lexer	*current;

	new = NULL;
	new = make_lex_node(new, token, str);
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
	new->next = NULL;
	return (1);
}
