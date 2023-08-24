/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:44:18 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/24 11:09:34 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executor(t_data *data)
{
	int		ret;

	data->old_exit_stat = g_exit_status;
	g_exit_status = 0;
	ret = make_heredocs(data);
	if (ret != 0)
	{
		g_exit_status = ret;
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
