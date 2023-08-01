/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 21:13:00 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/01 12:53:14 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// waits for all child processes and gets exit status of last one
static int	wait_for_children(int size, pid_t *pid)
{
	int	stat;
	int	i;

	i = 0;
	while (i < size)
	{
		if (pid[i] > 0)
			waitpid(pid[i], &stat, 0);
		i++;
	}
	free(pid);
	return (WEXITSTATUS(stat));
}

// expands cmd, creates 1st child process
static void	first_cmd(t_data *data, int fd_io[], int orig_pipe[], pid_t *pid)
{
	t_cmd	*cmd;

	cmd = data->cmds;
	expand_cmd(cmd->cmd_argv);
	cmd->fd_io = fd_io;
	if (cmd->redirects)
		cmd->fd_io = redirects(cmd, cmd->fd_io);
	if (cmd->cmd_argv)
	{
		pid[0] = fork();
		if (pid[0] == -1)
			exit_error(NULL, NULL, 1);
		if (pid[0] == 0)
			first_child(data, cmd, orig_pipe);
	}
	close(orig_pipe[1]);
}

// expands cmd, creates last child process
static void	last_cmd(t_data *data, int fd_io[], int orig_pipe[], pid_t last_pid)
{
	t_cmd	*cmd;

	cmd = find_last_cmd(data->cmds);
	expand_cmd(cmd->cmd_argv);
	cmd->fd_io = fd_io;
	if (cmd->redirects)
		cmd->fd_io = redirects(cmd, cmd->fd_io);
	if (cmd->cmd_argv)
	{
		last_pid = fork();
		if (last_pid == -1)
			exit_error(NULL, NULL, 1);
		if (last_pid == 0)
			last_child(data, cmd, orig_pipe);
	}
	close(orig_pipe[0]);
}

// loops through cmds, expands them, creates 2nd pipe and middle child processes
// QUESTION: can vars in cmds struct help wit norm errors?
static int	multi_pipes(t_data *data, int size, int fd_io[], int pipe_in[], pid_t *pid)
{
	t_cmd	*cmd;
	int		pipe_out[2];
	int		i;

	cmd = (data->cmds)->next;
	i = 1;
	while (i < size - 1)
	{
		expand_cmd(cmd->cmd_argv);
		cmd->fd_io = fd_io;
		if (cmd->redirects)
			cmd->fd_io = redirects(cmd, cmd->fd_io);
		if (i != 1)
			pipe_in[0] = pipe_out[0];
		if (pipe(pipe_out) == -1)
			exit_error(NULL, NULL, 1);
		if (cmd->cmd_argv)
		{
			pid[i] = fork();
			if (pid[i] == -1)
				exit_error(NULL, NULL, 1);
			if (pid[i] == 0)
				middle_child(data, cmd, pipe_in, pipe_out);
		}
		close(pipe_out[1]);
		cmd = cmd->next;
		i++;
	}
	return (pipe_out[0]);
}

// creates process ids, initializes them and creates 1st pipe
int	pipex(t_data *data, int size, int fd_io[])
{
	pid_t	*pid;
	int		orig_pipe[2];
	int		i;

	pid = ft_calloc(size, sizeof(pid_t));
	if (!pid)
		exit_error(NULL, NULL, 1);
	if (pipe(orig_pipe) == -1)
		exit_error(NULL, NULL, 1);
	i = 0;
	while (i < size)
	{
		pid[i] = -1;
		i++;
	}
	first_cmd(data, fd_io, orig_pipe, pid);
	if (size > 2)
		orig_pipe[0] = multi_pipes(data, size, fd_io, orig_pipe, pid);
	last_cmd(data, fd_io, orig_pipe, pid[size - 1]);
	return (wait_for_children(size, pid));
}
