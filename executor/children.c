/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/27 21:15:46 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/01 13:34:16 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// no pipes, only fd_in and fd_out
void	only_child(t_data *data, t_cmd *cmd)
{
	if (cmd->fd_io[0] != STDIN_FILENO)
	{
		if (dup2(cmd->fd_io[0], STDIN_FILENO) == -1)
			exit_error(NULL, NULL, 1);
		close(cmd->fd_io[0]);
	}
	if (cmd->fd_io[1] != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_io[1], STDOUT_FILENO) == -1)
			exit_error(NULL, NULL, 1);
		close(cmd->fd_io[1]);
	}
	run_cmd(data, cmd->args);
}

// reads from fd_in and writes to write-end of pipe (unless redirects)
void	first_child(t_data *data, t_cmd *cmd, int pipe_out[])
{
	close(pipe_out[0]);
	if (cmd->fd_io[0] != STDIN_FILENO)
	{
		if (dup2(cmd->fd_io[0], STDIN_FILENO) == -1)
			exit_error(NULL, NULL, 1);
		close(cmd->fd_io[0]);
	}
	if (dup2(pipe_out[1], STDOUT_FILENO) == -1)
		exit_error(NULL, NULL, 1);
	close(pipe_out[1]);
	if (cmd->fd_io[1] != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_io[1], STDOUT_FILENO) == -1)
			exit_error(NULL, NULL, 1);
		close(cmd->fd_io[1]);
	}
	run_cmd(data, cmd->args);
}

// reads from one pipe (unless redirects) and writes to next (unless redirects)
void	middle_child(t_data *data, t_cmd *cmd, int pipe_in[], int pipe_out[])
{
	close(pipe_out[0]);
	if (dup2(pipe_in[0], STDIN_FILENO) == -1)
		exit_error(NULL, NULL, 1);
	close(pipe_in[0]);
	if (dup2(pipe_out[1], STDOUT_FILENO) == -1)
		exit_error(NULL, NULL, 1);
	close(pipe_out[1]);
	if (cmd->fd_io[0] != STDIN_FILENO)
	{
		if (dup2(cmd->fd_io[0], STDIN_FILENO) == -1)
			exit_error(NULL, NULL, 1);
		close(cmd->fd_io[0]);
	}
	if (cmd->fd_io[1] != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_io[1], STDOUT_FILENO) == -1)
			exit_error(NULL, NULL, 1);
		close(cmd->fd_io[1]);
	}
	run_cmd(data, cmd->args);
}

// reads from read-end of pipe (unless redirects) and writes to fd_out
void	last_child(t_data *data, t_cmd *cmd, int pipe_in[])
{
	if (dup2(pipe_in[0], STDIN_FILENO) == -1)
		exit_error(NULL, NULL, 1);
	close(pipe_in[0]);
	if (cmd->fd_io[0] != STDIN_FILENO)
	{
		if (dup2(cmd->fd_io[0], STDIN_FILENO) == -1)
			exit_error(NULL, NULL, 1);
		close(cmd->fd_io[0]);
	}
	if (cmd->fd_io[1] != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_io[1], STDOUT_FILENO) == -1)
			exit_error(NULL, NULL, 1);
		close(cmd->fd_io[1]);
	}
	run_cmd(data, cmd->args);
}
