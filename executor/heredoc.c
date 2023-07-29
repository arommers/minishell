/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 15:26:11 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/07/26 16:34:03 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// opens new hd file, reads and expands input, stores it in file
// IGNORE COMMENTED BIT: I use get_next_line instead of readline when testing
static void	create_heredoc(t_lexer *heredoc, char *filename, int isquoted)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!fd)
		exit_error(filename, NULL, 1);
	// line = readline("> ");
	line = get_next_line(0);
	while (line && ft_strncmp(heredoc->str, line, ft_strlen(heredoc->str)) != 0)
	{
		if (isquoted == 0 && ft_strchr(line, '$'))
			line = expand_var(line);
		// ft_putendl_fd(line, fd);
		ft_putstr_fd(line, fd);
		free(line);
		// line = readline("> ");
		line = get_next_line(0);
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
void	heredoc(t_cmds *cmds, t_lexer *heredoc)
{
	int		isquoted;

	if (cmds->hd_filename)
		free(cmds->hd_filename);
	cmds->hd_filename = generate_filename();
	isquoted = 0;
	if (quote_strchr(heredoc->str))
	{
		heredoc->str = expand_str(heredoc->str, 1);
		isquoted = 1;
	}
	create_heredoc(heredoc, cmds->hd_filename, isquoted);
}
