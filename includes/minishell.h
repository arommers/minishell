/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 13:52:37 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/30 16:48:52 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\x1B[96;1m[minishell]: \x1B[0m"

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
	// char		*builtins
	t_lexer			*re_dir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data {
	char			*input;
	t_lexer			*lexer;
	t_cmd			*cmds;
	int				nr_pipes;
}	t_data;

// Lexer Functions

int			tokenizer(t_data *data);
t_tokens	check_index(char *input, int i);
int			store_token(t_data *data, int i);
t_lexer		*make_lex_node(t_lexer *new, t_tokens token, char *str);
int			add_lex_node(t_lexer **head, t_tokens token, char *str);

// Lexer Utilities

int			is_space(char c);
void		free_lexer(t_lexer **head);
int			skip_spaces(char *str, int i);
int			check_quotes(char q);
int			store_quoted(char *input, int i, char q);

// Lexer List Functions

void		del_lex_node(t_lexer **head);
t_lexer		*make_lex_node(t_lexer *new, t_tokens token, char *str);
int			add_lex_node(t_lexer **head, t_tokens token, char *str);

// Parser Functions

int			parser(t_data *data);
void		group_tokens(t_data *data);
void		store_args(t_data *data, t_cmd *cmd, int i);
void		store_redir(t_lexer **lexer, t_cmd *cmd);

// Parser Utilities

int			count_args(t_lexer *head);
void		count_pipes(t_data *data);

//	Parser List Functions

t_cmd		*make_cmd_node(t_cmd *new);
t_cmd		*add_cmd_node(t_cmd **head);

//	Print Fucnctions

char		*make_str(char **head);
int			check_j(t_tokens token);
void		print_cmd_list(t_cmd *head);
void		print_lex_list(t_lexer *head);


#endif