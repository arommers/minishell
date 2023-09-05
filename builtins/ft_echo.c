/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 14:48:06 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/09/05 16:02:05 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// checks if cmd->args[i] is a hyphen followed by a number of 'n' chars
static int	check_option_n(char *str)
{
	int	i;

	if (!(str[0] && str[0] == '-'))
		return (0);
	if (!(str[1] && str[1] == 'n'))
		return (0);
	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i])
		return (0);
	return (1);
}

// prints each argument that is not "-n" separated by a space,
// followed by a newline if none of the arguments are "-n"
int	ft_echo(t_data *data, t_cmd *cmd)
{
	int	isoption_n;
	int	first_print;
	int	i;

	(void)data;
	isoption_n = 0;
	first_print = 1;
	i = 1;
	while (cmd->args[i])
	{
		if (check_option_n(cmd->args[i]) == 1)
			isoption_n = 1;
		else
		{
			if (first_print == 0)
				ft_putchar_fd(' ', cmd->fd_io[1]);
			ft_putstr_fd(cmd->args[i], cmd->fd_io[1]);
			first_print = 0;
		}
		i++;
	}
	if (isoption_n == 0)
		ft_putchar_fd('\n', cmd->fd_io[1]);
	return (0);
}
