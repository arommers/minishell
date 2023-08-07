/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 17:11:19 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/02 15:59:57 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// checks if char is a letter, digit or underscore
int	isvarchr(char c)
{
	if (isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

// counts len of string till the next variable
int	len_till_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !(str[i] == '$' && isvarchr(str[i + 1])))
		i++;
	return (i);
}

// counts len of variable in string
int	len_of_var(char *str)
{
	int	i;

	i = 1;
	while (isvarchr(str[i]))
		i++;
	return (i);
}
