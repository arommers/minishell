/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_del.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 12:43:31 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/24 15:07:43 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lexer(t_lexer **head)
{
	t_lexer	*tmp;
	t_lexer	*current;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		tmp = current;
		if (current->chars)
			free(current->chars);
		current = current->next;
		free (tmp);
	}
	*head = NULL;
}

// Delete a node from the list and move the pointer to next

void	del_lex_node(t_lexer **head)
{
	t_lexer	*current;
	t_lexer	*tmp;

	current = *head;
	// if (current->token == 0)
	// 	// printf("DEL_NODE: %s\n", current->chars);
	// else
	// 	// printf("DEL_NODE: %d\n", current->token);
	if (current)
	{
		tmp = current;
		current = current->next;
		if (tmp->chars)
			free(tmp->chars);
		free(tmp);
	}
	*head = current;
}
