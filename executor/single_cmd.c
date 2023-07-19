/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 17:04:08 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/07/19 17:22:44 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// creates only child process, waits for it and gets exit status
void	single_cmd(t_data *data, int fd_io[])
{
	pid_t	pid;
	int		stat;

	if (!data->cmds->cmd_argv)
		exit(EXIT_SUCCESS);
	pid = fork();
	if (pid == -1)
		exit_error(NULL, NULL, 1);
	if (pid == 0)
		only_child(data, data->cmds, fd_io);
	waitpid(pid, &stat, 0);
	exit(WEXITSTATUS(stat));
}
