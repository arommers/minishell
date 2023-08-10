/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 16:42:32 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/10 16:02:03 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// either expands infile and opens it, or creates heredoc
static int	redirect_input(t_cmd *cmd, t_lexer *tmp, int fd_in)
{
	char	*infile;

	if (tmp->token == LESS)
	{
		if (quote_strchr(tmp->chars) || ft_strchr(tmp->chars, '$'))
		{
			tmp->chars = expand_str(tmp->chars, 0);
			if (!tmp->chars)
				return (-1);
		}
		infile = tmp->chars;
		fd_in = open(infile, O_RDONLY);
		if (fd_in == -1)
			return (print_error(infile, NULL), -1);
	}
	else
	{
		if (heredoc(cmd, tmp) == 1)
			return (-1);
		fd_in = -2;
	}
	return (fd_in);
}

// expands outfile, opens/creates it in either trunc- or append-mode
static int	redirect_output(t_lexer *tmp, int fd_out)
{
	char	*outfile;

	if (quote_strchr(tmp->chars) || ft_strchr(tmp->chars, '$'))
	{
		tmp->chars = expand_str(tmp->chars, 0);
		if (!tmp->chars)
			return (-1);
	}
	outfile = tmp->chars;
	if (tmp->token == GREAT)
		fd_out = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
		return (print_error(outfile, NULL), -1);
	return (fd_out);
}

// loops through redirects, separates input- from output-tokens,
// checks if last input-token was a heredoc
static int	*handle_redir(t_cmd *cmd, int fd_io[])
{
	t_lexer	*tmp;

	tmp = cmd->re_dir;
	while (tmp)
	{
		if (tmp->token == LESS || tmp->token == LESSLESS)
			fd_io[0] = redirect_input(cmd, tmp, fd_io[0]);
		else
			fd_io[1] = redirect_output(tmp, fd_io[1]);
		if (fd_io[0] == -1 || fd_io[1] == -1)
			return (free(fd_io), NULL);
		tmp = tmp->next;
	}
	if (fd_io[0] == -2)
	{
		fd_io[0] = open(cmd->hd_filename, O_RDONLY);
		if (fd_io[0] == -1)
		{
			print_error(cmd->hd_filename, NULL);
			return (free(fd_io), NULL);
		}
	}
	return (fd_io);
}

// QUESTION: is this the best way to initialize fd_io[]?
int	*redirects(t_cmd *cmd)
{
	int		*fd_io;

	fd_io = ft_calloc(2, sizeof(int));
	if (!fd_io)
		return (print_error(NULL, NULL), NULL);
	fd_io[0] = STDIN_FILENO;
	fd_io[1] = STDOUT_FILENO;
	if (cmd->re_dir)
		fd_io = handle_redir(cmd, fd_io);
	return (fd_io);
}
