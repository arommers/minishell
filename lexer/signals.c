/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/12 14:45:38 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/28 12:51:20 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	Initialize the signal function with their specific ctrl input
	- If the signals are received in interactive mode ctrl messages are supressed
	- If not in interactive mode the echo settings are restored */

void	init_signals( int i)
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
	if (i == 3)
	{
		signal(SIGINT, handle_sigint_hd);
		signal(SIGQUIT, SIG_IGN);
	}
}
