/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 15:26:11 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/10 19:10:26 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// opens new hd file, reads and expands input, stores it in file
static int	create_heredoc(t_data *data, t_lexer *heredoc,
						char *filename, int isquoted)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!fd)
		return (print_error(filename, NULL), 1);
	line = readline("> ");
	while (line && ft_strncmp(heredoc->chars, line, 
			ft_strlen(heredoc->chars)) != 0)
	{
		if (isquoted == 0 && ft_strchr(line, '$'))
		{
			line = expand_var(data, line);
			if (!line)
				return (1);
		}
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	close(fd);
	return (0);
}

// generates new filename using a static int
static char	*generate_filename(void)
{
	static int	i;
	char		*number;
	char		*filename;

	i++;
	number = ft_itoa(i);
	if (!number)
		return (NULL);
	filename = ft_strjoin("obj/.tmp_hd_file_", number);
	if (!filename)
		print_error(NULL, NULL);
	free(number);
	return (filename);
}

// replaces old heredoc, checks for quotes and makes new one
int	heredoc(t_data *data, t_cmd *cmd, t_lexer *heredoc)
{
	int		isquoted;

	if (cmd->hd_filename)
		free(cmd->hd_filename);
	cmd->hd_filename = generate_filename();
	if (!cmd->hd_filename)
		return (1);
	isquoted = 0;
	if (quote_strchr(heredoc->chars))
	{
		heredoc->chars = expand_str(data, heredoc->chars, 1);
		if (!heredoc->chars)
			return (1);
		isquoted = 1;
	}
	return (create_heredoc(data, heredoc, cmd->hd_filename, isquoted));
}
