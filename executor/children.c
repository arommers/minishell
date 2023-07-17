/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/27 21:15:46 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/07/17 19:51:57 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// no pipes, only fd_in and fd_out
void	only_child(t_data *data, t_cmds *cmd, int fd_io[])
{
	if (fd_io[0] != STDIN_FILENO)
	{
		if (dup2(fd_io[0], STDIN_FILENO) == -1)
			exit_error(NULL, NULL, 1);
		close(fd_io[0]);
	}
	if (fd_io[1] != STDOUT_FILENO)
	{
		if (dup2(fd_io[1], STDOUT_FILENO) == -1)
			exit_error(NULL, NULL, 1);
		close(fd_io[1]);
	}
	run_cmd(data, cmd->cmd_argv);
}

// reads from fd_in and writes to write-end of pipe
void	first_child(t_data *data, t_cmds *cmd, int fd_io[], int pipe_out[])
{
	if (fd_io[1] != STDOUT_FILENO)
		close(fd_io[1]);
	close(pipe_out[0]);
	if (fd_io[0] != STDIN_FILENO)
	{
		if (dup2(fd_io[0], STDIN_FILENO) == -1)
			exit_error(NULL, NULL, 1);
		close(fd_io[0]);
	}
	if (dup2(pipe_out[1], STDOUT_FILENO) == -1)
		exit_error(NULL, NULL, 1);
	close(pipe_out[1]);
	run_cmd(data, cmd->cmd_argv);
}

// reads from one pipe and writes to another
void	middle_child(t_data *data, t_cmds *cmd, int pipe_in[], int pipe_out[])
{
	close(pipe_out[0]);
	if (dup2(pipe_in[0], STDIN_FILENO) == -1)
		exit_error(NULL, NULL, 1);
	close(pipe_in[0]);
	if (dup2(pipe_out[1], STDOUT_FILENO) == -1)
		exit_error(NULL, NULL, 1);
	close(pipe_out[1]);
	run_cmd(data, cmd->cmd_argv);
}

// reads from read-end of pipe and writes to fd_out
void	last_child(t_data *data, t_cmds *cmd, int pipe_in[], int fd_io[])
{
	if (dup2(pipe_in[0], STDIN_FILENO) == -1)
		exit_error(NULL, NULL, 1);
	close(pipe_in[0]);
	if (fd_io[1] != STDOUT_FILENO)
	{
		if (dup2(fd_io[1], STDOUT_FILENO) == -1)
			exit_error(NULL, NULL, 1);
		close(fd_io[1]);
	}
	run_cmd(data, cmd->cmd_argv);
}
