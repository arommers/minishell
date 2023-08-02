/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:44:18 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/02 14:03:33 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// exits program in case of error (CHANGE TO FIT MINISHELL)
// cmd =		if running specific command causes the error
// err_msg =	error message in case error occurs in minishell itself
//				(so can't use perror)
void	exit_error(char *cmd, char *err_msg, int exit_code)
{
	if (err_msg)
	{
		if (cmd)
			ft_printf(2, "minishell: %s: %s\n", cmd, err_msg);
		else
			ft_printf(2, "minishell: %s\n", err_msg);
	}
	else
	{
		if (cmd)
			ft_printf(2, "minishell: %s: ", cmd);
		else
			ft_printf(2, "minishell:");
		perror(NULL);
	}
	exit(exit_code);
}

int	main(void)
{
	int		size;
	t_data	*data;

	data = NULL;
	size = cmds_size(data->cmds);
	if (size == 1)
		single_cmd(data);
	else
		pipex(data, size);
	return (0);
}
