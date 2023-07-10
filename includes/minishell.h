/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 13:52:37 by arommers      #+#    #+#                 */
/*   Updated: 2023/07/10 15:05:30 by arommers      ########   odam.nl         */
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

# define PROMPT "\x1B[96;1m[minishell]:\x1B[0m"

enum e_type {
	WORD,
	WHITE_SPACE,
	PIPE,
	LESS,
	LESS_LESS,
	GREAT,
	GREAT_GREAT,
};

enum e_state {
	DEFAULT,
	IN_SQUOTE,
	IN_DQUOTE,
};
typedef struct s_lexer {
	char			*data;
	int				len;
	enum e_type		*type;
	enum e_state	*state;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

#endif