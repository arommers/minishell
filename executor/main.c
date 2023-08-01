/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:44:18 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/01 12:46:46 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// exits program in case of error (CHANGE TO FIT MINISHELL)
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
static char	**make_argv(char *cmd, char *arg)
{
	char	**cmd_argv;

	cmd_argv = malloc(sizeof(char *) * 3);
	cmd_argv[0] = ft_strdup(cmd);
	cmd_argv[1] = ft_strdup(arg);
	cmd_argv[2] = NULL;
	return (cmd_argv);
}

// IGNORE: dummy data
static void	fill_data(t_data *data, char **envp)
{
	t_cmd	*cmds;
	// t_cmd	*cmds2;
	// t_lexer	*redirects2;

	data->envp = envp;
	cmds = malloc(sizeof(t_cmd));
	cmds->redirects = NULL;
	// cmds->redirects = malloc(sizeof(t_lexer));
	// redirects2 = malloc(sizeof(t_lexer));
	// cmds2 = malloc(sizeof(t_cmd));
	data->cmds = cmds;
	// cmds->hd_filename = NULL;
	// cmds->redirects->token = LESSER;
	// cmds->redirects->str = ft_strdup("end");
	// cmds->redirects->next = NULL;
	// redirects2->token = GREATER;
	// redirects2->str = ft_strdup("outfile.txt");
	// redirects2->next = NULL;
	cmds->cmd_argv = make_argv("echo", "\"Hello, I am \'$USER\'\"");
	cmds->next = NULL;
	// cmds2->cmd_argv = make_argv("uniq");
	// cmds2->next = NULL;
}

// QUESTION: is this the best way to initialize fd_io[]?
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
	if (!fd_io)
		exit_error(NULL, NULL, 1);
	fd_io[0] = STDIN_FILENO;
	fd_io[1] = STDOUT_FILENO;
	size = cmds_size(data->cmds);
	if (size == 1)
		single_cmd(data, fd_io);
	else
		pipex(data, size, fd_io);
	free(fd_io);
	return (0);
}
