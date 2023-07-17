/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:44:18 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/07/17 19:52:17 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// exits program in case of error
// cmd =		if running specific command causes the error
// err_msg =	error message in case error occurs in minishell itself
//				(so can't use perror)
void	exit_error(char *cmd, char *err_msg, int exit_code)
{
	if (err_msg)
	{
		if (cmd)
			ft_printf(2, "minishell: %s: %s\n", cmd, err_msg);
		else
			ft_printf(2, "minishell: %s\n", err_msg);
	}
	else
	{
		if (cmd)
			ft_printf(2, "minishell: %s: ", cmd);
		else
			ft_printf(2, "minishell:");
		perror(NULL);
	}
	exit(exit_code);
}

// dummy data, ignore
static char	**make_argv(char *cmd)
{
	char	**cmd_argv;

	cmd_argv = malloc(sizeof(char *) * 2);
	cmd_argv[0] = cmd;
	cmd_argv[1] = NULL;
	return (cmd_argv);
}

// dummy data, ignore
static void	fill_data(t_data *data, char **envp)
{
	t_cmds	*cmds;
	t_cmds	*cmds2;

	data->envp = envp;
	cmds = malloc(sizeof(t_cmds));
	cmds2 = malloc(sizeof(t_cmds));
	cmds->cmd_argv = make_argv("sort");
	cmds->next = cmds2;
	cmds2->cmd_argv = make_argv("uniq");
	data->cmds = cmds;
}

int	main(char **envp)
{
	t_data	*data;
	int		fd_io[2];
	int		size;

	data = malloc(sizeof(t_data));
	fill_data(data, envp);
	fd_io[0] = STDIN_FILENO;
	fd_io[1] = STDOUT_FILENO;
	if (data->cmds->redirects)
		*fd_io = redirects(data, fd_io);
	size = cmds_size(data->cmds);
	if (size == 1)
		single_cmd(data, fd_io);
	else
		pipex(data, size, fd_io);
	return (0);
}
