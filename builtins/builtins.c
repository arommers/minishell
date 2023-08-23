/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 14:47:38 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/23 11:49:40 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	run_builtin(t_data *data, t_cmd *cmd, int ischild)
{
	int	exit_stat;

	exit_stat = (*isbuiltin(cmd->args[0]))(data, cmd);
	if (ischild == 1)
		exit(exit_stat);
	return (exit_stat);
}
