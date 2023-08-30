/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pars_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 11:51:16 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/30 15:39:01 by arommers      ########   odam.nl         */
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
		if (current->hd_filename)
		{
			unlink(current->hd_filename);
			free(current->hd_filename);
		}
		if (current->fd_io)
			free(current->fd_io);
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
	{
		print_error(NULL, NULL);
		return (NULL);
	}
	new->args = NULL;
	new->re_dir = NULL;
	new->next = NULL;
	new->fd_io = NULL;
	new->hd_filename = NULL;
	return (new);
}

/*	Adds a new node to the cmd linked list.
	If the list points to NULL it creates a new head node. */

t_cmd	*add_cmd_node(t_data *data, t_cmd **head)
{
	t_cmd	*new;
	t_cmd	*current;

	new = NULL;
	new = make_cmd_node(new);
	if (!new)
	{
		free_lexer(&data->lexer);
		reset_data(data);
	}
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
