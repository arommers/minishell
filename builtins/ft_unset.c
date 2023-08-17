/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:01:38 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/17 15:17:47 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	del_var(t_data *data, char *var)
{
	t_lexer	*tmp;
	t_lexer	*ex_node;
	int		len;

	if (!ft_getenv(data, var))
		return ;
	len = ft_strlen(var);
	tmp = *(data->env);
	while (tmp && tmp->next)
	{
		if (ft_strncmp(tmp->next->chars, var, len) == 0
			&& tmp->next->chars[len] == '=')
		{
			ex_node = tmp->next;
			tmp->next = tmp->next->next;
			free(ex_node->chars);
			free(ex_node);
			return ;
		}
		tmp = tmp->next;
	}
}

static int	check_arg(char *var)
{
	int	i;

	if (!var[0] || ft_isdigit(var[0]))
		return (builtin_error("unset", var), 1);
	i = 0;
	while (var[i])
	{
		if (isvarchr(&var[i], 0) == 0)
			return (builtin_error("unset", var), 1);
		i++;
	}
	return (0);
}

int	ft_unset(t_data *data, t_cmd *cmd)
{
	int		exit_stat;
	int		ret;
	int		i;

	exit_stat = 0;
	i = 1;
	while (cmd->args[i])
	{
		ret = check_arg(cmd->args[i]);
		if (ret == 1)
			exit_stat = ret;
		if (ret == 0)
			del_var(data, cmd->args[i]);
		i++;
	}
	return (exit_stat);
}
