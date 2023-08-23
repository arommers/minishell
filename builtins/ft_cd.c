/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 17:20:27 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/23 15:53:55 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// uses ft_strjoin to create new environment strings to replace the old ones
// or add new variables to the environment
static int	update_pwds(t_data *data, char *old_pwd, char *new_pwd)
{
	char	*oldpwd_str;
	char	*pwd_str;

	oldpwd_str = ft_strjoin("OLDPWD=", old_pwd);
	if (!oldpwd_str)
	{
		print_error(NULL, NULL);
		return (free(old_pwd), free(new_pwd), 1);
	}
	free(old_pwd);
	pwd_str = ft_strjoin("PWD=", new_pwd);
	if (!pwd_str)
	{
		print_error(NULL, NULL);
		return (free(new_pwd), free(oldpwd_str), 1);
	}
	free(new_pwd);
	if (alter_env(data, oldpwd_str, "OLDPWD") == 1)
		return (free(pwd_str), 1);
	return (alter_env(data, pwd_str, "PWD"));
}

// either takes home directory as path if there is no cmd->args[1],
// or joins home directory with the string after '~'
static char	*make_home_path(t_data *data, t_cmd *cmd)
{
	char	*path;

	if (!ft_getenv(data, "HOME"))
		return (builtin_error("cd", "HOME", NULL), NULL);
	if (!cmd->args[1])
		path = ft_strdup(ft_getenv(data, "HOME"));
	else
		path = ft_strjoin(ft_getenv(data, "HOME"), &cmd->args[1][1]);
	if (!path)
		print_error(NULL, NULL);
	return (path);
}

// checks cmd->args[1] to zee if HOME or OLDPWD variables are involved,
// otherwise dups cmd->args[1] as is
static char	*make_path(t_data *data, t_cmd *cmd)
{
	char	*path;

	if (!cmd->args[1])
		return (make_home_path(data, cmd));
	if (cmd->args[1][0] == '~' && (!cmd->args[1][1] || cmd->args[1][1] == '/'))
		return (make_home_path(data, cmd));
	if (cmd->args[1][0] == '-' && !cmd->args[1][1])
	{
		if (ft_getenv(data, "OLDPWD"))
			path = ft_strdup(ft_getenv(data, "OLDPWD"));
		else
			return (builtin_error("cd", "OLDPWD", NULL), NULL);
	}
	else
		path = ft_strdup(cmd->args[1]);
	if (!path)
		print_error(NULL, NULL);
	return (path);
}

// makes new path, stores old cwd, uses chdir to change cwd into new path,
// and stores old and new cwd in the environment
int	ft_cd(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	path = make_path(data, cmd);
	if (!path)
		return (1);
	old_pwd = get_pwd();
	if (!old_pwd)
		return (free(path), 1);
	if (chdir(path) == -1)
	{
		builtin_error("cd", NULL, path);
		return (free(path), free(old_pwd), 1);
	}
	if (cmd->args[1][0] == '-' && !cmd->args[1][1])
		ft_putendl_fd(path, cmd->fd_io[1]);
	free(path);
	new_pwd = get_pwd();
	if (!new_pwd)
		return (free(old_pwd), 1);
	return (update_pwds(data, old_pwd, new_pwd));
}
