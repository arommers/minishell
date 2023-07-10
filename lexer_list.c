/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 14:52:19 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/10 15:04:44 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_lexer	*new_node(t_lexer *head, char *content)