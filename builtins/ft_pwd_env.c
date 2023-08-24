/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 15:08:18 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/24 17:06:50 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// gets current working directory from get_pwd and prints it
int	ft_pwd(t_data *data, t_cmd *cmd)
{
	char	*pwd;

	(void)cmd;
	(void)data;
	pwd = get_pwd();
	if (!pwd)
		return (1);
	ft_putendl_fd(pwd, cmd->fd_io[1]);
	free(pwd);
	return (0);
}

// loops through environment and prints each line (unless cmd->args[1])
int	ft_env(t_data *data, t_cmd *cmd)
{
	t_lexer	*tmp;

	if (cmd->args[1])
	{
		print_error(cmd->args[0], "too many arguments (none allowed)");
		return (1);
	}
	tmp = *(data->env);
	while (tmp)
	{
		if (cmd->args[0][1] == 'x')
			ft_putstr_fd("declare -x ", cmd->fd_io[1]);
		ft_putendl_fd(tmp->chars, cmd->fd_io[1]);
		tmp = tmp->next;
	}
	return (0);
}
