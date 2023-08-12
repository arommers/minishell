/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 21:13:00 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/10 19:03:39 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// waits for child processes and gets exit status of last one
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

// loops through cmds, expands them, creates middle child processes
static int	multi_pipes(t_data *data, t_cmd *cmd, pid_t *pid, int i)
{
	while (i < data->nr_pipes)
	{
		if (expand_cmd(data, cmd->args) == 1)
			return (1);
		cmd->fd_io = redirects(data, cmd);
		if (!cmd->fd_io)
			return (1);
		if (i != 1)
			data->pipe_1[0] = data->pipe_2[0];
		if (pipe(data->pipe_2) == -1)
			return (print_error(NULL, NULL), 1);
		if (cmd->args)
		{
			pid[i] = fork();
			if (pid[i] == -1)
				return (print_error(NULL, NULL), 1);
			if (pid[i] == 0)
				child(data, cmd, data->pipe_1, data->pipe_2);
		}
		close(data->pipe_2[1]);
		data->pipe_2[1] = -1;
		cmd = cmd->next;
		i++;
	}
	return (0);
}

static int	init_pipes(t_data *data)
{
	data->pipe_1 = ft_calloc(2, sizeof(int));
	if (!data->pipe_1)
		return (print_error(NULL, NULL), 1);
	data->pipe_1[0] = -1;
	data->pipe_1[1] = -1;
	if (data->nr_pipes > 1)
	{
		data->pipe_2 = ft_calloc(2, sizeof(int));
		if (!data->pipe_2)
			return (print_error(NULL, NULL), 1);
		data->pipe_2[0] = -1;
		data->pipe_2[1] = -1;
	}
	return (0);
}

// creates and initializes pipes and process ids
static pid_t	*init_tools(t_data *data)
{
	pid_t	*pid;
	int		i;

	if (init_pipes(data) == 1)
		return (NULL);
	pid = ft_calloc(data->nr_pipes + 1, sizeof(pid_t));
	if (!pid)
		return (print_error(NULL, NULL), NULL);
	i = 0;
	while (i < data->nr_pipes + 1)
	{
		pid[i] = -1;
		i++;
	}
	return (pid);
}

// initializes tools, calls cmd functions and returns wait function
int	pipex(t_data *data)
{
	pid_t	*pid;
	int		i;

	pid = init_tools(data);
	if (!pid)
		return (pipex_error(data, NULL));
	if (pipe(data->pipe_1) == -1)
		return (pipex_error(data, pid));
	if (first_cmd(data, pid) == 1)
		return (pipex_error(data, pid));
	if (data->nr_pipes > 1)
	{
		i = 1;
		if (multi_pipes(data, data->cmds->next, pid, i) == 1)
			return (pipex_error(data, pid));
		data->pipe_1[0] = data->pipe_2[0];
	}
	if (last_cmd(data, pid) == 1)
		return (pipex_error(data, pid));
	return (wait_for_children(data, pid));
}
