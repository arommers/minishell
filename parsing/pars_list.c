/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pars_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 11:51:16 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/26 16:17:30 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Intializes a new cmd node.
	sets all it's members to NULL.
*/

t_cmd	*make_cmd_node(t_cmd *new)
{
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->re_dir = NULL;
	new->next = NULL;
	return (new);
}

/*	Adds a new node to the cmd linked list.
	If the lists points to NULL it creates a new head node .
*/

t_cmd	*add_cmd_node(t_cmd **head)
{
	t_cmd	*new;
	t_cmd	*current;

	new = NULL;
	new = make_cmd_node(new);
	if (!new)
		return (NULL);
	if (!*head)
	{
		*head = new;
		return (new);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
	new->next = NULL;
	return (new);
}

/*	Go over the lex list and store any encountered tokens
	and subsequent filenames iin a new linked list.
	The list itself will be stored in the cmd node.
	The original nodes are deleted from the lext list
	and the pointer moved up. */

void	store_redir(t_lexer **head, t_cmd *cmd)
{
	t_lexer	*current;

	current = *head;
	while (current && current->token == WORDS)
		current = current->next;
	if (!current || current->token == PIPE)
		return ;
	// if (!current->next)
	// 	no filename errors etc
	// if (current->next->token)
	// 	double token errors etc
	if (current->token > 1 && current->token < 6)
	{
		add_lex_node(&cmd->re_dir, current->token, current->next->chars);
		del_lex_node(head, (*head)->index);
		del_lex_node(head, (*head)->index);
	}
	store_redir(head, cmd);
}
