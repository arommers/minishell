/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pars_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 11:51:16 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/24 17:42:02 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*make_cmd_node(t_cmd *new, t_data *data)
{
	t_cmd	*new;

	new = malloc(sizof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->re_dir = NULL;
	new->next = NULL;
	return (new);
}

t_cmd	*add_cmd_node(t_cmd **head, t_data *data)
{
	t_cmd	*new;
	t_cmd	*current;

	new = make_cmd_node(head, data);
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

// void	*del_redir(t_lexer *head)
// {
// 	t_lexer	*current;

// 	current = head;
// 	while ()
// }

t_lexer	*store_redir(t_lexer **head, t_cmd *cmd)
{
	t_lexer	*current;
	t_lexer	*re_dir;

	current = *head;
	re_dir = NULL;
	while (current && current->token == WORDS)
	{
		if (!current || current->token == PIPE)
			return (re_dir);
		// if ( 2 consecutive wrong tokens)
		// error;
		if (current && (current->token > 1 && current->token < 6))
		{
			add_lex_node(&re_dir, current->token, current->chars);
			del_lex_node(&current, current->index);
			del_lex_node(&current, current->index);
		}
		else
			current = current->next;
	}
	*head = current;
	return (re_dir);
}
