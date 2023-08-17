/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 15:08:18 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/17 16:17:15 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_data *data, t_cmd *cmd)
{
	char	*pwd;

	(void)cmd;
	(void)data;
	pwd = get_pwd();
	if (!pwd)
		return (1);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

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
		ft_putendl_fd(tmp->chars, 1);
		tmp = tmp->next;
	}
	return (0);
}
