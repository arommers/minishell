/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_util.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 12:48:00 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/30 14:53:14 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Sigint handler in interactive mode */

void	handle_sigint_ia(int sig)
{
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 128 + sig;
}

/*	Sigint handelr for heredoc mode */
void	handle_sigint_hd(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	exit (g_exit_status = 1);
}

/*	Sigint handler when interacting with a cmd*/

void	handle_sigint(int sig)
{
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit_status = 128 + sig;
}

/*	Sigquit handler when interacting with a cmd */

void	handle_sigquit(int sig)
{
	ft_putstr_fd("Quit: ", 2);
	ft_putnbr_fd(sig, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 128 + sig;
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
