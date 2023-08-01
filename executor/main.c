/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:44:18 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/01 13:00:00 by mgoedkoo      ########   odam.nl         */
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

// QUESTION: is this the best way to initialize fd_io[]?
int	main(t_data *data)
{
	int		*fd_io;
	int		size;

	fd_io = malloc(sizeof(int) * 2);
	if (!fd_io)
		exit_error(NULL, NULL, 1);
	fd_io[0] = STDIN_FILENO;
	fd_io[1] = STDOUT_FILENO;
	size = cmds_size(data->cmds);
	if (size == 1)
		single_cmd(data, fd_io);
	else
		pipex(data, size, fd_io);
	free(fd_io);
	return (0);
}
