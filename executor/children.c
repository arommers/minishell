/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/27 21:15:46 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/28 16:06:17 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	dup_fds(int fd_1, int fd_2)
{
	if (dup2(fd_1, fd_2) == -1)
		exit_error(NULL, NULL, 1);
}

// dups pipes if there are pipes, then dups redirects if there are redirects
void	child(t_data *data, t_cmd *cmd, int pipe_in[], int pipe_out[])
{
	if (pipe_in)
	{
		close(pipe_in[1]);
		dup_fds(pipe_in[0], STDIN_FILENO);
		close(pipe_in[0]);
	}
	if (pipe_out)
	{
		close(pipe_out[0]);
		dup_fds(pipe_out[1], STDOUT_FILENO);
		close(pipe_out[1]);
	}
	if (cmd->fd_io[0] != STDIN_FILENO)
	{
		dup_fds(cmd->fd_io[0], STDIN_FILENO);
		close(cmd->fd_io[0]);
	}
	if (cmd->fd_io[1] != STDOUT_FILENO)
	{
		dup_fds(cmd->fd_io[1], STDOUT_FILENO);
		close(cmd->fd_io[1]);
	}
	if (isbuiltin(cmd->args[0]))
		run_builtin(data, cmd, 1);
	run_cmd(data, cmd->args);
}
