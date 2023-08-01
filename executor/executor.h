/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:46:58 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/08/01 14:06:58 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char			**envp;
	struct s_cmd	*cmds;
}	t_data;

typedef enum s_tokens
{
	WORDS,
	PIPE,
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT,
}	t_tokens;

typedef struct s_lexer
{
	int				is_token;
	char			*chars;
	t_tokens		token;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_cmd
{
	char			**args;
	char			*hd_filename;
	int				*fd_io;
	t_lexer			*re_dir;
	struct s_cmd	*next;
}	t_cmd;

int		cmds_size(t_cmd *cmds);
void	exit_error(char *cmd, char *err_msg, int exit_code);
void	expand_cmd(char **cmd_argv);
char	*expand_str(char *str, int isheredoc);
char	*expand_var(char *str);
t_cmd	*find_last_cmd(t_cmd *cmds);
void	first_child(t_data *data, t_cmd *cmd, int pipe_out[]);
void	heredoc(t_cmd *cmds, t_lexer *heredoc);
int		isquote(char c);
int		isvarchr(char c);
char	*join_new_str(char **tmp_array);
void	last_child(t_data *data, t_cmd *cmd, int pipe_in[]);
int		len_of_var(char *str);
int		len_till_quote(char *str, char quote);
int		len_till_var(char *str);
void	middle_child(t_data *data, t_cmd *cmd, int pipe_in[], int pipe_out[]);
void	only_child(t_data *data, t_cmd *cmd);
int		pipex(t_data *data, int size, int fd_io[]);
char	*quote_strchr(char *str);
int		*redirects(t_cmd *cmd, int fd_io[]);
void	run_cmd(t_data *data, char **cmd_argv);
int		single_cmd(t_data *data, int fd_io[]);

#endif