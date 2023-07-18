/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:46:58 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/07/18 14:34:03 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <stdio.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*var;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_env			*envp;
	struct s_cmds	*cmds;
}	t_data;

typedef enum s_tokens
{
	WORDS,
	PIPE,
	GREAT,
	GREATER,
	LESS,
	LESSER
}	t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_cmds
{
	char			**cmd_argv;
	int				(*builtin)(t_data *, struct s_cmds *);
	char			*hd_file;
	t_lexer			*redirects;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

int		cmds_size(t_cmds *cmds);
void	exit_error(char *cmd, char *err_msg, int exit_code);
t_cmds	*find_last_cmd(t_cmds *cmds);
void	first_child(t_data *data, t_cmds *cmd, int fd_in, int pipe_out[]);
void	last_child(t_data *data, t_cmds *cmd, int pipe_in[], int fd_out);
void	middle_child(t_data *data, t_cmds *cmd, int pipe_in[], int pipe_out[]);
void	only_child(t_data *data, t_cmds *cmd, int fd_io[]);
void	pipex(t_data *data, int size, int fd_io[]);
int		*redirects(t_data *data, int fd_io[]);
void	run_cmd(t_data *data, char **cmd_argv);
void	single_cmd(t_data *data, int fd_io[]);

#endif