/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   store_redir.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 15:19:16 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/30 16:14:48 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_current(t_data *data, t_lexer **head)
{
	t_lexer	*current;

	current = *head;
	while (current && current->token == WORDS && !current->is_token)
		current = current->next;
	if (!current || current->token == PIPE)
		return (0);
	if (!current->next)
		syntax_error(data, WORDS);
	if (current->next->token)
		syntax_error(data, current->next->token);
	*head = current;
	return (1);
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
	char	*str;

	current = *head;
	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	if (!check_current(data, &current))
		return ;
	if (current->token > 1 && current->token < 6)
	{
		current->is_token = 1;
		current->next->is_token = 1;
		str = ft_strdup(current->next->chars);
		if (!str)
			return (print_error(NULL, NULL), free_lexer(&data->lexer),
				reset_data(data));
		if (!add_lex_node(&tmp->re_dir, current->token, str))
			reset_data(data);
		current = current->next->next;
		str = NULL;
	}
	store_redir(data, &current, cmd);
}
