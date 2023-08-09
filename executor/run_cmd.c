/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/27 20:41:26 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/09 16:38:36 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// loops through paths from the env variable until it finds working path
// to command, exits program if no working path is found
static char	*try_all_paths(char *cmd, char **all_paths, char *cmd_path)
{
	char	*full_path;
	int		i;

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
	if (!all_paths[i])
		exit_error(cmd, "command not found", 127);
	free_chrarray(all_paths);
	free(cmd_path);
	return (full_path);
}

// tries all paths to command that are not paths from the env variable
static char	*get_path(char *cmd, char *envp_paths)
{
	char	*cmd_path;
	char	**all_paths;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	cmd_path = ft_strjoin("/", cmd);
	if (!cmd_path)
		exit_error(NULL, NULL, 1);
	if (access(cmd_path, F_OK | X_OK) == 0)
		return (cmd_path);
	all_paths = ft_split(envp_paths, ':');
	if (!all_paths)
		exit_error(NULL, NULL, 1);
	free(envp_paths);
	return (try_all_paths(cmd, all_paths, cmd_path));
}

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
	while (env)
	{
		envp[i] = env->chars;
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

// looks for working path to command before executing command
void	run_cmd(t_data *data, char **cmd_argv)
{
	char	**envp;
	char	*envp_paths;
	char	*work_path;

	envp = make_envp(data->env);
	work_path = cmd_argv[0];
	if (getenv("PATH"))
	{
		envp_paths = ft_strdup(getenv("PATH"));
		if (!envp_paths)
			exit_error(NULL, NULL, 1);
		work_path = get_path(cmd_argv[0], envp_paths);
	}
	if (execve(work_path, cmd_argv, envp) == -1)
		exit_error(work_path, NULL, 126);
}
