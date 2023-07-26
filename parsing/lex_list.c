/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 16:03:16 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/26 13:29:36 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_j(t_tokens token)
{
	if (token == PIPE)
		return (1);
	else if (token == LESS)
		return (2);
	else if (token == LESSLESS)
		return (3);
	else if (token == GREAT)
		return (4);
	else
		return (5);
}

void	print_lex_list(t_lexer *head)
{
	char			*tmp[] = {"WORDS", "PIPE", "LESS", "LESSLESS", "GREAT", "GREATGREAT", NULL};
	t_lexer			*current;
	int				i;
	int				j;

	current = head;
	i = 0;
	while (current)
	{
		if (current->token == 0)
			printf("NODE %d: %s\n", current->index, current->chars);
		else
		{
			j = check_j(current->token);
			printf("NODE %d: %s\n", current->index, tmp[j]);
		}
		current = current->next;
		i++;
	}
}

// Create a new node for the lexer list

t_lexer	*make_lex_node(t_lexer *new, t_tokens token, char *str)
{
	static int	index;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->token = token;
	new->chars = str;
	new->index = index++;
	new->next = NULL;
	return (new);
}

// Creates a new node and adds it to the back of the doubly linked list

int	add_lex_node(t_lexer **head, t_tokens token, char *str)
{
	t_lexer	*new;
	t_lexer	*current;

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
