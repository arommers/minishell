/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 15:26:11 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/24 17:37:11 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// opens new hd file, reads and expands input, stores it in file, then exits
static void	heredoc_child(t_data *data, t_lexer *heredoc,
						char *filename, int isquoted)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!fd)
		return (print_error(filename, NULL), exit(EXIT_FAILURE));
	init_signals(data, 3);
	line = readline("> ");
	while (line && ft_strncmp(heredoc->chars, line, 
			ft_strlen(heredoc->chars)) != 0)
	{
		if (isquoted == 0 && ft_strchr(line, '$'))
		{
			line = expand_var(data, line);
			if (!line)
				exit(EXIT_FAILURE);
		}
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	exit(EXIT_SUCCESS);
}

// initializes signals and creates heredoc child process
static int	create_heredoc(t_data *data, t_lexer *heredoc,
						char *filename, int isquoted)
{
	pid_t	pid;
	int		stat;

	init_signals(data, 4);
	pid = fork();
	if (pid == -1)
		return (print_error(NULL, NULL), 1);
	if (pid == 0)
		heredoc_child(data, heredoc, filename, isquoted);
	waitpid(pid, &stat, 0);
	init_signals(data, 1);
	return (WEXITSTATUS(stat));
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

// replaces old heredoc filename, checks for quotes
static int	heredoc(t_data *data, t_cmd *cmd, t_lexer *heredoc)
{
	int		isquoted;

	if (cmd->hd_filename)
	{
		unlink(cmd->hd_filename);
		free(cmd->hd_filename);
	}
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

// loops through commands and redirects, makes heredocs if encountered
int	make_heredocs(t_data *data)
{
	t_cmd	*tmp_cmd;
	t_lexer	*tmp_re_dir;
	int		ret;

	tmp_cmd = data->cmds;
	while (tmp_cmd)
	{
		tmp_re_dir = tmp_cmd->re_dir;
		while (tmp_re_dir)
		{
			if (tmp_re_dir->token == LESSLESS)
			{
				ret = heredoc(data, tmp_cmd, tmp_re_dir);
				if (ret != 0)
					return (ret);
			}
			tmp_re_dir = tmp_re_dir->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}
