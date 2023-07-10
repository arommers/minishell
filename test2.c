/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 15:20:28 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/10 15:21:57 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	make_test(int i)
{
	if (i == 1)
		printf("merge succesfull");
	else
		printf("merge unsuccesfull");
	return (0);
}
