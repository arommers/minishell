/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 17:04:08 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/09 14:04:27 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// expands cmd, creates only child process, waits for it and gets exit status
int	single_cmd(t_data *data)
{
	pid_t	pid;
	int		stat;

	if (expand_cmd(data->cmds->args) == 1)
		return (1);
	data->cmds->fd_io = redirects(data->cmds);
	if (!data->cmds->fd_io)
		return (1);
	if (!data->cmds->args)
		return (0);
	pid = fork();
	if (pid == -1)
		exit_error(NULL, NULL, 1);
	if (pid == 0)
		child(data, data->cmds, NULL, NULL);
	waitpid(pid, &stat, 0);
	return (WEXITSTATUS(stat));
}
