/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pars_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 11:51:16 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/09 15:21:09 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_array(char **array)
{
	int		i;

	if (!array || !*array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

/*	Cleans a cmd list and each re_dir list associated with each specific node */

void	free_cmd_list(t_cmd **head)
{
	t_cmd	*current;
	t_cmd	*tmp;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		free_lexer(&current->re_dir);
		clear_array(current->args);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*head = NULL;
}

/*	Intializes a new cmd node; sets all members to NULL. */

t_cmd	*make_cmd_node(t_cmd *new)
{
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->re_dir = NULL;
	new->next = NULL;
	new->fd_io = NULL;
	new->hd_filename = NULL;
	return (new);
}

/*	Adds a new node to the cmd linked list.
	If the list points to NULL it creates a new head node. */

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
	return (*head);
}

/*	Go over the lex list and store any encountered tokens
	and subsequent filenames in a new linked list.
	The list itself will be stored in the cmd node.
	The original nodes are deleted from the lext list
	and the pointer moved up. */

void	store_redir(t_data *data, t_lexer **head, t_cmd *cmd)
{
	t_lexer	*current;
	t_cmd	*tmp;

	current = *head;
	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	while (current && current->token == WORDS && !current->is_token)
		current = current->next;
	if (!current || current->token == PIPE)
		return ;
	if (!current->next)
		syntax_error(data, WORDS);
	if (current->next->token)
		syntax_error(data, current->next->token);
	if (current->token > 1 && current->token < 6)
	{
		current->is_token = 1;
		current->next->is_token = 1;
		add_lex_node(&tmp->re_dir, current->token,
			ft_strdup(current->next->chars));
		current = current->next->next;
	}
	store_redir(data, &current, cmd);
}
