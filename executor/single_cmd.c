/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 17:04:08 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/24 11:11:23 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// expands cmd, creates child process, waits for it and gets exit status
int	single_cmd(t_data *data)
{
	pid_t	pid;
	int		stat;

	if (expand_cmd(data, data->cmds->args) == 1)
		return (1);
	data->cmds->fd_io = redirects(data, data->cmds);
	if (!data->cmds->fd_io)
		return (1);
	if (!data->cmds->args)
		return (0);
	if (isbuiltin(data->cmds->args[0]))
		return (run_builtin(data, data->cmds, 0));
	// init_signals(data, 4);
	pid = fork();
	if (pid == -1)
		return (print_error(NULL, NULL), 1);
	if (pid == 0)
		child(data, data->cmds, NULL, NULL);
	waitpid(pid, &stat, 0);
	return (WEXITSTATUS(stat));
}
