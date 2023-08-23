/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:44:18 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/23 15:14:35 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executor(t_data *data)
{
	int		ret;

	data->old_exit_stat = g_exit_status;
	g_exit_status = 0;
	if (make_heredocs(data) == 1)
	{
		g_exit_status = 1;
		return ;
	}
	init_signals(data, 2);
	if (data->nr_pipes == 0)
		ret = single_cmd(data);
	else
		ret = pipex(data);
	if (g_exit_status == 0)
		g_exit_status = ret;
}
