/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 13:52:37 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/14 15:00:24 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\x1B[96;1m[minishell]: \x1B[0m"

typedef enum s_tokens {
	PIPE,
	GREAT,
	GREATER,
	LESS,
	LESSER
}	t_tokens;

typedef struct s_lexer {
	char			*chars;
	t_tokens		*token;
	// int				len;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_data {
	char			*input;
	t_env			*env;
	char			*pwd;
	char			*oldpwd;
	t_lexer			*lexer;
}	t_data;

#endif