/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 15:18:45 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/21 17:10:42 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//	Store redirects in a linked list and remove them from the lexer list.
//	Store a simple command in a node and remove them from the leer list.

t_cmd	*group_tokens(t_data *data)
{
	t_cmd	*cmd_node;
	t_lexer	*re_dir;
	t_lexer	*current;
	int		args;

	cmd_node = NULL;
	re_dir = store_redir(data);
	store_arg(cmd_node, data);
	args = count_args(data->lexer);
	current = data->lexer;
	while (args)
	{
		cmd_node->
		args--;
	}
	return ();
}

// Iterate through the linked list, group commands into cmd struct.
// deleting stored parts until the original lexed list is gone.

int	parser(t_data *data)
{
	t_cmd	*cmd;

	cmd = NULL;
	// count_pipes(data);
	while (data->lexer)
	{
		if (data->lexer->token == PIPE)
			del_lex_node(&data->lexer, data->lexer->index);
		cmd = group_tokens(data);
		if (add_cmd_node(&cmd) != 1)
			return (0);
		reset_index(data->lexer);
	}
	return (1);
}
