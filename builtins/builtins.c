/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 14:47:38 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/24 16:24:04 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// checks if cmd->args[0] is a builtin command, and returns a pointer
// to the corresponding builtin function
int	(*isbuiltin(char *str))(t_data *data, t_cmd *cmd)
{
	if (ft_strncmp(str, "echo", ft_strlen(str) + 1) == 0)
		return (ft_echo);
	if (ft_strncmp(str, "cd", ft_strlen(str) + 1) == 0)
		return (ft_cd);
	if (ft_strncmp(str, "pwd", ft_strlen(str) + 1) == 0)
		return (ft_pwd);
	if (ft_strncmp(str, "export", ft_strlen(str) + 1) == 0)
		return (ft_export);
	if (ft_strncmp(str, "unset", ft_strlen(str) + 1) == 0)
		return (ft_unset);
	if (ft_strncmp(str, "env", ft_strlen(str) + 1) == 0)
		return (ft_env);
	if (ft_strncmp(str, "exit", ft_strlen(str) + 1) == 0)
		return (ft_exit);
	return (NULL);
}

// runs builtin function, gets its exit status, closes fds,
// and either exits or returns depending on child/parent process
int	run_builtin(t_data *data, t_cmd *cmd, int ischild)
{
	int	exit_stat;

	if (ischild == 1)
	{
		cmd->fd_io[0] = 0;
		cmd->fd_io[1] = 1;
	}
	exit_stat = (*isbuiltin(cmd->args[0]))(data, cmd);
	if (ischild == 1)
		exit(exit_stat);
	if (cmd->fd_io[0] != 0)
		close(cmd->fd_io[0]);
	if (cmd->fd_io[1] != 1)
		close(cmd->fd_io[1]);
	return (exit_stat);
}
