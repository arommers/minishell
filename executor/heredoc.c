/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 15:26:11 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/01 14:09:12 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// opens new hd file, reads and expands input, stores it in file
static void	create_heredoc(t_lexer *heredoc, char *filename, int isquoted)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!fd)
		exit_error(filename, NULL, 1);
	line = readline("> ");
	while (line && ft_strncmp(heredoc->chars, line, 
			ft_strlen(heredoc->chars)) != 0)
	{
		if (isquoted == 0 && ft_strchr(line, '$'))
			line = expand_var(line);
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	close(fd);
}

// generates new filename using a static int
static char	*generate_filename(void)
{
	static int	i;
	char		*number;
	char		*filename;

	i++;
	number = ft_itoa(i);
	filename = ft_strjoin("build/.tmp_hd_file_", number);
	if (!filename)
		exit_error(NULL, NULL, 1);
	return (filename);
}

// replaces old heredoc, checks for quotes and makes new one
void	heredoc(t_cmd *cmd, t_lexer *heredoc)
{
	int		isquoted;

	if (cmd->hd_filename)
		free(cmd->hd_filename);
	cmd->hd_filename = generate_filename();
	isquoted = 0;
	if (quote_strchr(heredoc->chars))
	{
		heredoc->chars = expand_str(heredoc->chars, 1);
		isquoted = 1;
	}
	create_heredoc(heredoc, cmd->hd_filename, isquoted);
}
