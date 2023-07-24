/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:44:18 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/07/24 17:33:53 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// exits program in case of error (CHANGE TO FIT MINISHELL !!!)
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

// IGNORE: dummy data
static char	**make_argv(char *cmd)
{
	char	**cmd_argv;

	cmd_argv = malloc(sizeof(char *) * 2);
	cmd_argv[0] = ft_strdup(cmd);
	cmd_argv[1] = NULL;
	return (cmd_argv);
}

// IGNORE: dummy data
static void	fill_data(t_data *data, char **envp)
{
	t_cmds	*cmds;
	t_cmds	*cmds2;
	// t_lexer	*redirects2;

	data->envp = envp;
	cmds = malloc(sizeof(t_cmds));
	cmds->redirects = malloc(sizeof(t_lexer));
	// redirects2 = malloc(sizeof(t_lexer));
	cmds2 = malloc(sizeof(t_cmds));
	data->cmds = cmds;
	cmds->hd_filename = NULL;
	cmds->redirects->token = LESSER;
	cmds->redirects->str = ft_strdup("one\'two\'\"three\"four\'\"five\"\'");
	cmds->redirects->next = NULL;
	// redirects2->token = GREATER;
	// redirects2->str = ft_strdup("outfile.txt");
	// redirects2->next = NULL;
	cmds->cmd_argv = make_argv("sort");
	cmds->next = cmds2;
	cmds2->cmd_argv = make_argv("uniq");
	cmds2->next = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		*fd_io;
	int		size;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	fill_data(data, envp);
	fd_io = malloc(sizeof(int) * 2);
	fd_io[0] = STDIN_FILENO;
	fd_io[1] = STDOUT_FILENO;
	if (data->cmds->redirects)
		fd_io = redirects(data, fd_io);
	size = cmds_size(data->cmds);
	if (size == 1)
		single_cmd(data, fd_io);
	else
		pipex(data, size, fd_io);
	return (0);
}
