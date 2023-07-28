/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 15:18:45 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/28 16:07:36 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*	Store the arguments in the cmd struct 
	and delete the nodes from the original list */

void	store_args(t_data *data, t_cmd *cmd, int i)
{
	t_cmd	*tmp;
	int		j;

	j = 0;
	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->args = ft_calloc (i + 1, sizeof(char *));
	// if (!cmd->arg)
	// 	error;
	// printf("test_arg\n");
	while (i)
	{
		tmp->args[j++] = ft_strdup(data->lexer->chars);
		del_lex_node(&(data->lexer));
		i--;
	}
}

/*	Store redirects in a linked list and remove them from the lexer list.
	Store a simple command in a node and remove them from the lexer list.
	Each cmd node has its own list for redirects. */

void	group_tokens(t_data *data)
{
	data->cmds = add_cmd_node(&(data->cmds));
	printf("starting point group token: %s\n", data->lexer->chars);
	store_redir(&(data->lexer), data->cmds);
	printf("test3\n");
	print_lex_list(data->lexer);
	printf("store arg\n");
	store_args(data, data->cmds, count_args(data->lexer));
	print_cmd_list(data->cmds);
}

/*	Iterate through the linked list, group commands into cmd nodes,
	deleting stored parts until the original lexed list is gone. */

int	parser(t_data *data)
{
	count_pipes(data);
	while (data->lexer)
	{
		if (data->lexer->token == PIPE)
			del_lex_node(&(data->lexer));
		group_tokens(data);
	}
	return (1);
}
