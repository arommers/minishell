/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 15:18:45 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/24 17:15:07 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//	Store redirects in a linked list and remove them from the lexer list.
//	Store a simple command in a node and remove them from the leer list.
//	Each cmd node has its own list for redirects

t_cmd	*group_tokens(t_data *data, t_cmd *cmd)
{
	t_cmd	*new;
	t_lexer	*current;
	int		args;

	cmd = add_cmd_node(&cmd, data);
	cmd->re_dir = store_redir(&data->lexer, cmd);
	store_arg(new, data);
	args = count_args(data->lexer);
	current = data->lexer;
	while (args)
	{
		new->
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
		group_tokens(data, cmd);
		reset_index(data->lexer);
	}
	return (1);
}
