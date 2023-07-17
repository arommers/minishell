/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 16:03:16 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/17 09:58:12 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_lex_list(t_lexer *head)
{
	t_lexer			*current;
	int				i;

	current = head;
	i = 0;
	while (current)
	{
		printf("NODE %d: %d\n", i, current->token);
		i++;
		current = current->next;
	}
}

// Create a new node for the lexer list

t_lexer	*make_node(t_lexer *new, t_tokens token, char *str)
{
	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	// new->chars = str;
	new->token = token;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

// Creates a new node and adds it to the back of the doubly linked list

int	add_node(t_lexer **head, t_tokens token, char *str)
{
	t_lexer	*new;
	t_lexer	*current;

	new = make_node(new, token, str);
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
