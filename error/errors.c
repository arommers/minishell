/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/08 15:23:01 by adri          #+#    #+#                 */
/*   Updated: 2023/08/12 11:33:55 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quote_error(t_data *data, char c)
{
	if (c == '\"') 
		ft_putendl_fd(E_PROMPT "unexpected EOF while looking for matching `\"'", 2);
	else if (c == '\'') 
		ft_putendl_fd(E_PROMPT "unexpected EOF while looking for matching `\''", 2);
	else if (c == ';')
		ft_putendl_fd(E_PROMPT "syntax error near unexpected token `;'", 2);
	else if (c == '\\')
		ft_putstr_fd(E_PROMPT "syntax error near unexpected token `\\'", 2);
	reset_data(data);
}

void	syntax_error(t_data *data, t_tokens token)
{
	ft_putstr_fd(E_PROMPT "syntax error near unexpected token ", 2);
	if (token == WORDS)
		ft_putendl_fd("`newline'", 2);
	else if (token == PIPE)
		ft_putendl_fd("`|'", 2);
	else if (token == LESS)
		ft_putendl_fd("`<'", 2);
	else if (token == LESSLESS)
		ft_putendl_fd("`<<'", 2);
	else if (token == GREAT)
		ft_putendl_fd("`>'", 2);
	else if (token == GREATGREAT)
		ft_putendl_fd("`>>'", 2);
	else if (token == AND)
		ft_putendl_fd("`&'", 2);
	free_lexer(&data->lexer);
	reset_data(data);
}
