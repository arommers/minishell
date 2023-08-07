/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_util.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 17:22:01 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/07 16:44:21 by mgoedkoo      ########   odam.nl         */
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
void	first_cmd(t_data *data, int orig_pipe[], pid_t first_pid)
{
	t_cmd	*cmd;

	cmd = data->cmds;
	expand_cmd(cmd->args);
	cmd->fd_io = redirects(cmd);
	if (cmd->args)
	{
		first_pid = fork();
		if (first_pid == -1)
			exit_error(NULL, NULL, 1);
		if (first_pid == 0)
			first_child(data, cmd, orig_pipe);
	}
	close(orig_pipe[1]);
}

// expands cmd, creates last child process
void	last_cmd(t_data *data, int orig_pipe[], pid_t last_pid)
{
	t_cmd	*cmd;

	cmd = find_last_cmd(data->cmds);
	expand_cmd(cmd->args);
	cmd->fd_io = redirects(cmd);
	if (cmd->args)
	{
		last_pid = fork();
		if (last_pid == -1)
			exit_error(NULL, NULL, 1);
		if (last_pid == 0)
			last_child(data, cmd, orig_pipe);
	}
	close(orig_pipe[0]);
}
