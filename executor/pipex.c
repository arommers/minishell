/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 21:13:00 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/07/18 14:33:21 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// waits for all child processes and gets exit status of last one
static void	wait_for_children(int size, pid_t *pid)
{
	int	stat;
	int	i;

	i = 0;
	while (i < size)
	{
		waitpid(pid[i], &stat, 0);
		i++;
	}
	free(pid);
	exit(WEXITSTATUS(stat));
}

// creates 1st child process
static void	first_cmd(t_data *data, int fd_io[], int orig_pipe[], pid_t *pid)
{
	pid[0] = fork();
	if (pid[0] == -1)
		exit_error(NULL, NULL, 1);
	if (pid[0] == 0)
		first_child(data, data->cmds, fd_io, orig_pipe);
	close(orig_pipe[1]);
}

// creates last child process
static void	last_cmd(t_data *data, int orig_pipe[], int fd_io[], pid_t last_pid)
{
	last_pid = fork();
	if (last_pid == -1)
		exit_error(NULL, NULL, 1);
	if (last_pid == 0)
		last_child(data, find_last_cmd(data->cmds), orig_pipe, fd_io);
	close(orig_pipe[0]);
}

// creates 2nd pipe and switches between both pipes in middle child processes
static int	multi_pipes(t_data *data, int size, int pipe_in[], pid_t *pid)
{
	t_cmds	*cmd;
	int		pipe_out[2];
	int		i;

	cmd = (data->cmds)->next;
	i = 1;
	while (i < size - 1)
	{
		if (i != 1)
			pipe_in[0] = pipe_out[0];
		if (pipe(pipe_out) == -1)
			exit_error(NULL, NULL, 1);
		pid[i] = fork();
		if (pid[i] == -1)
			exit_error(NULL, NULL, 1);
		if (pid[i] == 0)
			middle_child(data, cmd, pipe_in, pipe_out);
		close(pipe_out[1]);
		cmd = cmd->next;
		i++;
	}
	return (pipe_out[0]);
}

// creates process ids and 1st pipe
void	pipex(t_data *data, int size, int fd_io[])
{
	pid_t	*pid;
	int		orig_pipe[2];

	pid = malloc(sizeof(pid_t) * size);
	if (!pid)
		exit_error(NULL, NULL, 1);
	if (pipe(orig_pipe) == -1)
		exit_error(NULL, NULL, 1);
	first_cmd(data, fd_io, orig_pipe, pid);
	if (size > 2)
		orig_pipe[0] = multi_pipes(data, size, orig_pipe, pid);
	last_cmd(data, orig_pipe, fd_io, pid[size - 1]);
	wait_for_children(size, pid);
}
