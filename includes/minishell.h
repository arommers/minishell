/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 13:52:37 by arommers      #+#    #+#                 */
/*   Updated: 2023/08/09 13:27:52 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\x1B[96;1m[minishell]: \x1B[0m"
# define E_PROMPT "minishell: "

typedef enum s_tokens {
	WORDS,
	PIPE,
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT,
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
	char			**env;
	t_lexer			*lexer;
	t_cmd			*cmds;
	int				nr_pipes;
}	t_data;

void		init_data(t_data *data);
void		reset_data(t_data *data);
void		maintain_prompt(t_data *data);

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

void		syntax_error(t_data *data, t_tokens token);

//	Print Functions

char		*make_str(char **head);
int			check_j(t_tokens token);
void		print_cmd_list(t_cmd *head);
void		print_lex_list(t_lexer *head);

// Expander functions

int			isquote(char c);
int			isvarchr(char c);
int			len_of_var(char *str);
char		*expand_var(char *str);
int			len_till_var(char *str);
char		*quote_strchr(char *str);
void		expand_cmd(char **cmd_argv);
char		*join_new_str(char **tmp_array);
int			len_till_quote(char *str, char quote);
char		*expand_str(char *str, int isheredoc);

// Executor functions

void		child(t_data *data, t_cmd *cmd, int pipe_in[], int pipe_out[]);
void		executor(t_data *data);
int			*redirects(t_cmd *cmd);
int			single_cmd(t_data *data);
int			pipex(t_data *data);
void		run_cmd(t_data *data, char **cmd_argv);
void		heredoc(t_cmd *cmds, t_lexer *heredoc);
void		exit_error(char *cmd, char *err_msg, int exit_code);
void		last_cmd(t_data *data, int pipe_in[], pid_t last_pid);
void		first_cmd(t_data *data, int pipe_out[], pid_t first_pid);
void		free_chrarray(char **array);

#endif