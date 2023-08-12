/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:44:18 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/10 18:02:13 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executor(t_data *data)
{
	if (data->nr_pipes == 0)
		data->exit_stat = single_cmd(data);
	else
		data->exit_stat = pipex(data);
}
