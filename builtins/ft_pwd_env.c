/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 15:08:18 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/15 18:32:21 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_data *data, t_cmd *cmd)
{
	char	*buffer;

	(void)cmd;
	if (ft_getenv(data, "PWD"))
		ft_putendl_fd(ft_getenv(data, "PWD"), 1);
	else
	{
		buffer = ft_calloc(200, sizeof(char));
		buffer = getcwd(buffer, 200);
		if (!buffer)
			return (print_error(NULL, NULL), 1);
		ft_putendl_fd(buffer, 1);
		free(buffer);
		buffer = NULL;
	}
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
