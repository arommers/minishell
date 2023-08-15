/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 14:48:06 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/15 15:04:02 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_option_n(char *str)
{
	int	i;

	if (!(str[0] && str[0] == '-'))
		return (0);
	if (!str[1] && str[1] == 'n')
		return (0);
	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	ft_echo(t_data *data, t_cmd *cmd)
{
	int	isoption_n;
	int	i;

	(void)data;
	isoption_n = 0;
	if (cmd->args[1])
		isoption_n = find_option_n(cmd->args[1]);
	i = 1;
	while (cmd->args[i])
	{
		if (i > 2 || (i == 2 && isoption_n == 0))
			ft_putchar_fd(' ', 1);
		if (!(i == 1 && isoption_n == 1))
			ft_putstr_fd(cmd->args[i], 1);
		i++;
	}
	if (isoption_n == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
