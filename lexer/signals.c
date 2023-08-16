/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/12 14:45:38 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/16 16:43:35 by mgoedkoo      ########   odam.nl         */
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
	g_exit_status = 1;
}

/*	sigint in non interactive mode*/

void	handle_sigint(int sig)
{
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit_status = 128 + sig;
}

/*	sigquit in non interactive mode */

void	handle_sigquit(int sig)
{
	ft_putstr_fd("Quit: ", 2);
	ft_putnbr_fd(sig, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 128 + sig;
}

/*	Initialize the signal function with their specific ctrl input
	- If the signals are received in interactive mode ctrl messages are supressed
	- If not in interactive mode the echo settings are restored */

void	init_signals(t_data *data, int i)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	if (i == 1)
	{
		signal(SIGINT, handle_sigint_ia);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 2)
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
	}
}
