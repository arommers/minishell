/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_errors.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 15:44:43 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/15 17:11:53 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// exits program in case of error in child process
// cmd =		if running specific command causes the error
// err_msg =	error message in case error occurs in minishell itself
//				(so can't use perror)
void	exit_error(char *cmd, char *err_msg, int exit_code)
{
	if (err_msg)
	{
		if (cmd)
			ft_printf(2, "minishell: %s: %s\n", cmd, err_msg);
		else
			ft_printf(2, "minishell: %s\n", err_msg);
	}
	else
	{
		if (cmd)
			ft_printf(2, "minishell: %s: ", cmd);
		else
			ft_printf(2, "minishell:");
		perror(NULL);
	}
	exit(exit_code);
}

// prints error message in case of error in parent process
// cmd =		if running specific command causes the error
// err_msg =	error message in case error occurs in minishell itself
//				(so can't use perror)
void	print_error(char *cmd, char *err_msg)
{
	if (err_msg)
	{
		if (cmd)
			ft_printf(2, "minishell: %s: %s\n", cmd, err_msg);
		else
			ft_printf(2, "minishell: %s\n", err_msg);
	}
	else
	{
		if (cmd)
			ft_printf(2, "minishell: %s: ", cmd);
		else
			ft_printf(2, "minishell:");
		perror(NULL);
	}
}

void	var_error(char *cmd, char *var)
{
	ft_printf(2, "minishell: %s: `%s': ", cmd, var);
	ft_printf(2, "not a valid identifier\n");
}

// frees process ids and closes pipes in case of pipex error
int	pipex_error(t_data *data, pid_t *pid)
{
	if (pid)
		free(pid);
	if (data->pipe_1[0] != -1)
		close(data->pipe_1[0]);
	if (data->pipe_1[1] != -1)
		close(data->pipe_1[1]);
	if (data->pipe_2)
	{
		if (data->pipe_2[0] != -1)
			close(data->pipe_2[0]);
		if (data->pipe_2[1] != -1)
			close(data->pipe_2[1]);
	}
	return (1);
}
