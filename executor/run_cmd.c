/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/27 20:41:26 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/07/17 19:52:42 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// loops through paths from the env variable until it finds working path to command,
// exits program if no working path is found
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
			return (full_path);
		free(full_path);
		full_path = NULL;
		i++;
	}
	exit_error(cmd, "command not found", 127);
	return (NULL);
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
	return (try_all_paths(cmd, all_paths, cmd_path));
}

// loops through env list until the PATH variable is found
static char	*find_envp_paths(t_env *envp, char *envp_paths)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp && !ft_strnstr(tmp->var, "PATH", ft_strlen(tmp->var)))
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	envp_paths = ft_strdup(tmp->var + 5);
		if (!envp_paths)
			exit_error(NULL, NULL, 1);
	return (envp_paths);
}

// looks for working path to command before executing command
void	run_cmd(t_data *data, char **cmd_argv)
{
	char	*envp_paths;
	char	*work_path;

	work_path = cmd_argv[0];
	envp_paths = NULL;
	envp_paths = find_envp_paths(data->envp, envp_paths);
	if (envp_paths)
		work_path = get_path(cmd_argv[0], envp_paths);
	if (execve(work_path, cmd_argv, data->envp) == -1)
		exit_error(work_path, NULL, 126);
}
