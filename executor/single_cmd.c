/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 17:04:08 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/02 15:59:12 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// expands cmd, creates only child process, waits for it and gets exit status
int	single_cmd(t_data *data)
{
	pid_t	pid;
	int		stat;

	expand_cmd(data->cmds->args);
	data->cmds->fd_io = redirects(data->cmds);
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
