/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 15:18:45 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/30 13:19:09 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Store the arguments in the cmd struct */
// QUESTION: Add malloc protection for ft_strdup here?
void	store_args(t_data *data, t_cmd *cmd, int i, int j)
{
	t_lexer	*current;
	t_cmd	*tmp;

	tmp = cmd;
	current = data->lexer;
	while (tmp->next)
		tmp = tmp->next;
	if (i == 0)
	{
		tmp->args = NULL;
		return ;
	}
	tmp->args = ft_calloc(i + 1, sizeof(char *));
	if (!tmp->args)
	{
		print_error(NULL, NULL);
		reset_data(data);
	}
	while (current && current->token != PIPE)
	{
		if (!current->is_token)
			tmp->args[j++] = ft_strdup(current->chars);
		current = current->next;
	}
	tmp->args[j] = NULL;
}

/*	Make a cmd node, store redirects in a linked list
	and store a simple command in a node. Each cmd node has its own redir list.
	Delete the nodes from the lexer that were stored. */
// QUESTION: What if data->cmds == NULL because of malloc error?
void	group_tokens(t_data *data)
{
	data->cmds = add_cmd_node(&data->cmds);
	store_redir(data, &data->lexer, data->cmds);
	store_args(data, data->cmds, count_args(data->lexer), 0);
	while (data->lexer && data->lexer->token != PIPE)
		del_lex_node(&data->lexer);
}

/*	Iterate through the linked list, group commands into cmd nodes,
	deleting stored parts until the original lexed list is gone. */

int	parser(t_data *data)
{
	count_pipes(data);
	while (data->lexer)
	{
		if (data->lexer->token == PIPE)
			del_lex_node(&data->lexer);
		group_tokens(data);
	}
	return (1);
}
