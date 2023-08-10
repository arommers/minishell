/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 21:13:00 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/10 16:14:35 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// waits for all child processes and gets exit status of last one
static int	wait_for_children(t_data *data, pid_t *pid)
{
	int	stat;
	int	i;

	i = 0;
	while (i < data->nr_pipes + 1)
	{
		if (pid[i] > 0)
			waitpid(pid[i], &stat, 0);
		i++;
	}
	free(pid);
	return (WEXITSTATUS(stat));
}

// loops through cmds, expands them, creates 2nd pipe and middle child processes
static int	multi_pipes(t_data *data, int pipe_in[], pid_t *pid, int i)
{
	t_cmd	*cmd;
	int		pipe_out[2];

	cmd = (data->cmds)->next;
	while (i < data->nr_pipes)
	{
		if (expand_cmd(cmd->args) == 1)
			return (-1);
		cmd->fd_io = redirects(cmd);
		if (!cmd->fd_io)
			return (-1);
		if (i != 1)
			pipe_in[0] = pipe_out[0];
		if (pipe(pipe_out) == -1)
			return (print_error(NULL, NULL), -1);
		if (cmd->args)
		{
			pid[i] = fork();
			if (pid[i] == -1)
				return (print_error(NULL, NULL), -1);
			if (pid[i] == 0)
				child(data, cmd, pipe_in, pipe_out);
		}
		close(pipe_out[1]);
		cmd = cmd->next;
		i++;
	}
	return (pipe_out[0]);
}

// creates process ids, initializes them and creates 1st pipe
int	pipex(t_data *data)
{
	pid_t	*pid;
	int		orig_pipe[2];
	int		i;

	pid = ft_calloc(data->nr_pipes + 1, sizeof(pid_t));
	if (!pid)
		return (print_error(NULL, NULL), 1);
	if (pipe(orig_pipe) == -1)
	{
		print_error(NULL, NULL);
		return (free(pid), 1);
	}
	i = 0;
	while (i < data->nr_pipes + 1)
	{
		pid[i] = -1;
		i++;
	}
	if (first_cmd(data, orig_pipe, pid[0]) == 1)
		return (free(pid), 1);
	if (data->nr_pipes > 1)
	{
		i = 1;
		orig_pipe[0] = multi_pipes(data, orig_pipe, pid, i);
		if (orig_pipe[0] == -1)
			return (free(pid), 1);
	}
	if (last_cmd(data, orig_pipe, pid[data->nr_pipes]) == 1)
		return (free(pid), 1);
	return (wait_for_children(data, pid));
}
