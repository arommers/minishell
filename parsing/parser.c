/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 15:18:45 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/21 12:09:46 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	group_tokens(t_lexer *head)
{
	t_lexer	*current;
	int		args;

	args = count_args(head);
	current = head;
}

t_cmd	*init_cmd(t_cmd *cmd)
{
	
}

int	parser(t_data *data)
{
	t_cmd	*cmd;

	cmd = NULL;
	count_pipes(data);
	while (data->lexer)
	{
		cmd = init_cmd(data->lexer);
		group_tokens(data->lexer);
	}
	return (1);
}
