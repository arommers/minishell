/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 15:18:45 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/26 16:14:49 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Store the arguments in the cmd struct 
	and delete the nodes from the original list */

void	store_args(t_data *data, t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	cmd->args = malloc (i * sizeof(char *));
	// if (!cmd->arg)
	// 	error;
	while (i)
	{
		cmd->args[j++] = ft_strdup(data->lexer->chars);
		del_lex_node(&data->lexer, data->lexer->index);
		i--;
	}
}

/*	Store redirects in a linked list and remove them from the lexer list.
	Store a simple command in a node and remove them from the leer list.
	Each cmd node has its own list for redirects. */

void	group_tokens(t_data *data, t_cmd *cmd)
{
	cmd = add_cmd_node(&cmd);
	store_redir(&data->lexer, cmd);
	store_args(data, cmd, count_args(data->lexer));
}

/*	Iterate through the linked list, group commands into cmd struct.
	deleting stored parts until the original lexed list is gone. */

int	parser(t_data *data)
{
	t_cmd	*cmd;

	cmd = NULL;
	count_pipes(data);
	while (data->lexer)
	{
		if (data->lexer->token == PIPE)
			del_lex_node(&data->lexer, data->lexer->index);
		group_tokens(data, cmd);
	}
	return (1);
}
