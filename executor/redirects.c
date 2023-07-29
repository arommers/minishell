/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 16:42:32 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/07/26 16:33:41 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// either expands infile and opens it, or creates heredoc
static int	redirect_input(t_cmds *cmds, t_lexer *tmp, int fd_in)
{
	char	*infile;

	if (tmp->token == LESS)
	{
		if (quote_strchr(tmp->str) || ft_strchr(tmp->str, '$'))
			tmp->str = expand_str(tmp->str, 0);
		infile = tmp->str;
		fd_in = open(infile, O_RDONLY);
		if (fd_in == -1)
			exit_error(infile, NULL, 1);
	}
	else
	{
		heredoc(cmds, tmp);
		fd_in = -1;
	}
	return (fd_in);
}

// expands outfile, opens/creates it in either trunc- or append-mode
static int	redirect_output(t_lexer *tmp, int fd_out)
{
	char	*outfile;

	if (quote_strchr(tmp->str) || ft_strchr(tmp->str, '$'))
		tmp->str = expand_str(tmp->str, 0);
	outfile = tmp->str;
	if (tmp->token == GREAT)
		fd_out = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
		exit_error(outfile, NULL, 1);
	return (fd_out);
}

// loops through redirects, separates input- from output-tokens,
// checks if last input-token was a heredoc
int	*redirects(t_data *data, int fd_io[])
{
	t_lexer	*tmp;

	tmp = data->cmds->redirects;
	while (tmp)
	{
		if (tmp->token == LESS || tmp->token == LESSER)
			fd_io[0] = redirect_input(data->cmds, tmp, fd_io[0]);
		else
			fd_io[1] = redirect_output(tmp, fd_io[1]);
		tmp = tmp->next;
	}
	if (fd_io[0] == -1)
	{
		fd_io[0] = open(data->cmds->hd_filename, O_RDONLY);
		if (fd_io[0] == -1)
			exit_error(data->cmds->hd_filename, NULL, 1);
	}
	return (fd_io);
}
