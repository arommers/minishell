/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/27 20:41:26 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/09/01 12:47:14 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// loops through paths from the env variable until it finds working path
// to command, exits program if no working path is found
static char	*try_all_paths(char *cmd, char **all_paths)
{
	char	*cmd_path;
	char	*full_path;
	int		i;

	cmd_path = ft_strjoin("/", cmd);
	if (!cmd_path)
		exit_error(NULL, NULL, 1);
	i = 0;
	while (all_paths[i])
	{
		full_path = ft_strjoin(all_paths[i], cmd_path);
		if (!full_path)
			exit_error(NULL, NULL, 1);
		if (access(full_path, F_OK | X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_chrarray(all_paths);
	free(cmd_path);
	return (full_path);
}

// checks if command itself is an absolute or relative path
static int	cmd_is_path(char *cmd)
{
	if (!cmd[0])
		return (0);
	if (cmd[0] == '/')
		return (1);
	if (cmd[0] == '.')
	{
		if (!cmd[1])
			return (1);
		if (cmd[1] == '/')
			return (1);
		if (cmd[1] == '.')
		{
			if (!cmd[2])
				return (1);
			if (cmd[2] == '/')
				return (1);
		}
	}
	return (0);
}

static char	*get_path(t_data *data, char *cmd)
{
	char	**all_paths;
	char	*envp_paths;
	char	*full_path;

	envp_paths = ft_strdup(ft_getenv(data, "PATH"));
	if (!envp_paths)
		exit_error(NULL, NULL, 1);
	all_paths = ft_split(envp_paths, ':');
	if (!all_paths)
		exit_error(NULL, NULL, 1);
	free(envp_paths);
	full_path = try_all_paths(cmd, all_paths);
	if (!full_path)
		exit_error(cmd, "command not found", 127);
	return (full_path);
}

// makes a 2D array out of the environment linked list
static char	**make_envp(t_lexer *env)
{
	char	**envp;
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = ft_calloc(i + 1, sizeof(char *));
	if (!envp)
		exit_error(NULL, NULL, 1);
	i = 0;
	tmp = env;
	while (tmp)
	{
		envp[i] = tmp->chars;
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	run_cmd(t_data *data, char **cmd_argv)
{
	struct stat	*buf;
	char		**envp;
	char		*work_path;

	envp = make_envp(*(data->env));
	work_path = NULL;
	if (cmd_is_path(cmd_argv[0]) == 1 || !ft_getenv(data, "PATH"))
	{
		if (access(cmd_argv[0], F_OK) != 0)
			exit_error(cmd_argv[0], "No such file or directory", 127);
		buf = ft_calloc(1, sizeof(struct stat));
		if (!buf)
			exit_error(NULL, NULL, 1);
		if (stat(cmd_argv[0], buf) == -1)
			exit_error(NULL, NULL, 1);
		if (S_ISDIR(buf->st_mode) != 0)
			exit_error(cmd_argv[0], "is a directory", 126);
		free(buf);
		work_path = cmd_argv[0];
	}
	else
		work_path = get_path(data, cmd_argv[0]);
	if (execve(work_path, cmd_argv, envp) == -1)
		exit_error(work_path, NULL, 126);
}
