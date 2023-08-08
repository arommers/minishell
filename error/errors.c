/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/08 15:23:01 by adri          #+#    #+#                 */
/*   Updated: 2023/08/08 15:34:22 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    syntax_error(t_tokens token)
{
    ft_putstr_fd(PROMPT "syntax error near unexpected token ", 2);
    if (token == NULL)
        ft_putend_fd("`newline'", 2);
    else if (token == PIPE)
        ft_putend_fd("`|'", 2);
    else if (token == LESS)
        ft_putendl_fd("`<'", 2);
    else if (token == LESSLESS)
        ft_putendl_fd("`<<'", 2);
    else if (token == GREAT)
        ft_putendl_fd("`>'", 2);
    else if (token == GREATGREAT)
        ft_putendl_fd("`>>'", 2);
}