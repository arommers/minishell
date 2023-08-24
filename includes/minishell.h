/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 13:52:37 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/24 13:26:03 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\x1B[96;1m[minishell]: \x1B[0m"
# define E_PROMPT "minishell: "

int	g_exit_status;

typedef enum s_tokens {
	WORDS,
	PIPE,
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT,
	AND,
}	t_tokens;

typedef struct s_lexer {
	int				is_token;
	char			*chars; 
	t_tokens		token;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_cmd {
	char			**args;
	char			*hd_filename;
	int				*fd_io;
	t_lexer			*re_dir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data {
	char			*input;
	t_lexer			**env;
	t_lexer			*lexer;
	t_cmd			*cmds;
	int				*pipe_1;
	int				*pipe_2;
	int				nr_pipes;
	int				old_exit_stat;
}	t_data;

void		check_dup(t_data *data);
void		reset_data(t_data *data);
void		input_check(t_data *data);
void		check_u_quotes(t_data *data);
void		maintain_prompt(t_data *data);
void		init_signals(t_data *data, int i);
void		init_data(t_data *data, char **env);
void		rl_replace_line(const char *txt, int clear_undo);

// Lexer Functions

int			tokenizer(t_data *data);
t_tokens	check_index(char *input, int i);
int			store_token(t_data *data, int i);
t_lexer		*make_lex_node(t_lexer *new, t_tokens token, char *str);
int			add_lex_node(t_lexer **head, t_tokens token, char *str);

// Lexer Utilities

int			is_space(char c);
int			check_quotes(char q);
void		free_lexer(t_lexer **head);
int			skip_spaces(char *str, int i);
int			store_quoted(char *input, int i, char q);

// Lexer List Functions

void		del_lex_node(t_lexer **head);
t_lexer		*make_lex_node(t_lexer *new, t_tokens token, char *str);
int			add_lex_node(t_lexer **head, t_tokens token, char *str);

// Parser Functions

int			parser(t_data *data);
void		group_tokens(t_data *data);
void		store_args(t_data *data, t_cmd *cmd, int i);
void		store_redir(t_data *data, t_lexer **lexer, t_cmd *cmd);

// Parser Utilities

int			count_args(t_lexer *head);
void		count_pipes(t_data *data);

//	Parser List Functions

void		clear_array(char **array);
t_cmd		*make_cmd_node(t_cmd *new);
t_cmd		*add_cmd_node(t_cmd **head);
void		free_cmd_list(t_cmd **head);

//	Error Functions

void		quote_error(t_data *data, char c);
void		syntax_error(t_data *data, t_tokens token);
void		exit_error(char *cmd, char *err_msg, int exit_code);
int			pipex_error(t_data *data, pid_t *pid);
void		print_error(char *cmd, char *err_msg);
void		builtin_error(char *cmd, char *var, char *path);

//	Print Functions

char		*make_str(char **head);
int			check_j(t_tokens token);
void		print_cmd_list(t_cmd *head);
void		print_lex_list(t_lexer *head);

// Expander functions

int			isquote(char c);
int			isvarchr(char *str, int i);
int			len_of_var(char *str, int i);
char		*expand_var(t_data *data, char *str);
int			len_till_var(char *str, int i);
char		*quote_strchr(char *str);
int			expand_cmd(t_data *data, char **cmd_argv);
char		*join_new_str(char **tmp_array);
void		*free_chrarray(char **array);
int			len_till_quote(char *str, char quote);
char		*expand_str(t_data *data, char *str, int isheredoc);

// Executor functions

void		child(t_data *data, t_cmd *cmd, int pipe_in[], int pipe_out[]);
void		executor(t_data *data);
int			first_cmd(t_data *data, pid_t *pid);
int			last_cmd(t_data *data, pid_t *pid);
int			make_heredocs(t_data *data);
int			pipex(t_data *data);
int			*redirects(t_data *data, t_cmd *cmd);
void		run_cmd(t_data *data, char **cmd_argv);
int			single_cmd(t_data *data);

//	Signal functions

void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		handle_sigint_ia(int sig);
void		handle_sigint_hd(int sig);

// Builtin functions

char		*get_pwd(void);
char		*ft_getenv(t_data *data, char *str);
int			alter_env(t_data *data, char *str, char *var);
int			ft_cd(t_data *data, t_cmd *cmd);
int			ft_env(t_data *data, t_cmd *cmd);
int			ft_pwd(t_data *data, t_cmd *cmd);
int			ft_exit(t_data *data, t_cmd *cmd);
int			ft_echo(t_data *data, t_cmd *cmd);
int			ft_unset(t_data *data, t_cmd *cmd);
int			ft_export(t_data *data, t_cmd *cmd);
int			run_builtin(t_data *data, t_cmd *cmd, int ischild);
int			(*isbuiltin(char *str))(t_data *data, t_cmd *cmd);

int					str_isdigit(char *str);
unsigned long long	ft_atoll(const char *str);
void				set_exit_status(t_cmd *cmd, unsigned long long value);

#endif