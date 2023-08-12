/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_util.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 17:22:01 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/10 19:01:57 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// finds last command in list
static t_cmd	*find_last_cmd(t_cmd *cmds)
{
	while (cmds)
	{
		if (!cmds->next)
			return (cmds);
		cmds = cmds->next;
	}
	return (NULL);
}

// expands cmd, creates 1st child process
int	first_cmd(t_data *data, pid_t *pid)
{
	t_cmd	*cmd;

	cmd = data->cmds;
	if (expand_cmd(data, cmd->args) == 1)
		return (1);
	cmd->fd_io = redirects(data, cmd);
	if (!cmd->fd_io)
		return (1);
	if (cmd->args)
	{
		pid[0] = fork();
		if (pid[0] == -1)
			return (print_error(NULL, NULL), 1);
		if (pid[0] == 0)
			child(data, cmd, NULL, data->pipe_1);
	}
	close(data->pipe_1[1]);
	data->pipe_1[1] = -1;
	return (0);
}

// expands cmd, creates last child process
int	last_cmd(t_data *data, pid_t *pid)
{
	t_cmd	*cmd;

	cmd = find_last_cmd(data->cmds);
	if (expand_cmd(data, cmd->args))
		return (1);
	cmd->fd_io = redirects(data, cmd);
	if (!cmd->fd_io)
		return (1);
	if (cmd->args)
	{
		pid[data->nr_pipes] = fork();
		if (pid[data->nr_pipes] == -1)
			return (print_error(NULL, NULL), 1);
		if (pid[data->nr_pipes] == 0)
			child(data, cmd, data->pipe_1, NULL);
	}
	close(data->pipe_1[0]);
	data->pipe_1[0] = -1;
	return (0);
}
