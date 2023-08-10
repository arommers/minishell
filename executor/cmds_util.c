/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_util.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 17:22:01 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/10 16:07:09 by mgoedkoo      ########   odam.nl         */
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
int	first_cmd(t_data *data, int pipe_out[], pid_t first_pid)
{
	t_cmd	*cmd;

	cmd = data->cmds;
	if (expand_cmd(cmd->args) == 1)
		return (1);
	cmd->fd_io = redirects(cmd);
	if (!cmd->fd_io)
		return (1);
	if (cmd->args)
	{
		first_pid = fork();
		if (first_pid == -1)
			return (print_error(NULL, NULL), 1);
		if (first_pid == 0)
			child(data, cmd, NULL, pipe_out);
	}
	close(pipe_out[1]);
	return (0);
}

// expands cmd, creates last child process
int	last_cmd(t_data *data, int pipe_in[], pid_t last_pid)
{
	t_cmd	*cmd;

	cmd = find_last_cmd(data->cmds);
	if (expand_cmd(cmd->args))
		return (1);
	cmd->fd_io = redirects(cmd);
	if (!cmd->fd_io)
		return (1);
	if (cmd->args)
	{
		last_pid = fork();
		if (last_pid == -1)
			return (print_error(NULL, NULL), 1);
		if (last_pid == 0)
			child(data, cmd, pipe_in, NULL);
	}
	close(pipe_in[0]);
	return (0);
}
