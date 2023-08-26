/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 09:53:11 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/25 14:33:50 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "", 1) == 0)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

unsigned long long	ft_atoll(const char *str)
{
	unsigned long long	a;
	unsigned long long	b;
	int					i;

	a = 0;
	b = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			b = b * -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + str[i] - '0';
		i++;
	}
	return (a * b);
}

void	set_exit_status(t_cmd *cmd, unsigned long long value)
{
	if (cmd->args[1] && !str_isdigit(cmd->args[1]))
	{
		ft_putstr_fd(E_PROMPT, 2);
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit (255);
	}
	if (cmd->args[1] && value >= 0 && value < 256)
		g_exit_status = (int)value;
	else if (value < 0 || value > 255)
		g_exit_status = value % 256;
}

int	ft_exit(t_data *data, t_cmd *cmd)
{
	unsigned long long	value;

	(void) data;
	ft_putendl_fd("exit", 2);
	if (cmd->args[1])
	{
		value = ft_atoll(cmd->args[1]);
		if (cmd->args[1][0] != '-' && value > LLONG_MAX)
		{
			ft_putstr_fd(E_PROMPT, 2);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit (255);
		}
	}
	if (cmd->args[1] && str_isdigit(cmd->args[1]) && cmd->args[2])
	{
		ft_putendl_fd(E_PROMPT "exit: too many arguments", 2);
		return (1);
	}
	set_exit_status(cmd, value);
	if (!cmd->args[1])
		g_exit_status = 0;
	exit(g_exit_status);
}
