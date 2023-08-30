# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: arommers <arommers@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/07/20 13:38:03 by arommers      #+#    #+#                  #
#    Updated: 2023/08/30 15:26:27 by arommers      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g -Wno-unused-command-line-argument
NAME	=	minishell
LIBFT	=	./libft/libft.a
INCLUDE =	-I./includes

BREWRL1    = -I includes -I $(HOME)/.brew/Cellar/readline/8.2.1/include
BREWRL2    = -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline

SRC 	=	./lexer/main.c ./lexer/print.c						\
			./lexer/lexer.c ./lexer/lex_list.c					\
			./lexer/lex_util.c ./lexer/lex_del.c				\
			./parser/pars_list.c ./parser/pars_util.c			\
			./parser/parser.c ./expander/var_util.c				\
			./expander/expand_str.c ./expander/expand_util.c	\
			./expander/expand_var.c ./expander/quote_util.c		\
			./executor/children.c ./executor/cmds_util.c		\
			./executor/executor.c ./executor/heredoc.c			\
			./executor/pipex.c ./executor/redirects.c			\
			./executor/run_cmd.c ./executor/single_cmd.c		\
			./error/errors.c ./lexer/in_check.c					\
			./error/exec_errors.c ./builtins/builtins.c			\
			./builtins/ft_echo.c ./builtins/ft_pwd_env.c		\
			./builtins/ft_export.c ./lexer/signals.c			\
			./builtins/ft_unset.c ./builtins/ft_cd.c			\
			./builtins/ft_exit.c ./builtins/env_util.c			\
			./lexer/signal_util.c ./parser/store_redir.c


OBJ_DIR =	obj
OBJ		=	$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

BOLD    := \033[1m./SRC/
RED     := \033[31;1m
GREEN   := \033[32;1m
YELLOW  := \033[33;1m
BLUE    := \033[34;1m
MAGENTA := \033[35;1m
CYAN    := \033[36;1m
WHITE   := \033[37;1m
RESET	= \x1b[0m

START_M = 0

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "Compiled with $(BLUE) -Wall -Wextra -Werror $(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(BREWRL2) $(OBJ) $(LIBFT)
	@echo "$(CYAN)------------------------------------------"
	@echo "      $(NAME) = NOW READY FOR USE!"
	@echo "------------------------------------------$(RESET)"

$(LIBFT):
	@$(MAKE) -C ./libft

$(OBJ_DIR)/%.o: ./lexer/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiled ✅ $(CYAN) $^ $(RESET)"
	@$(CC) $(CFLAGS) $(BREWRL1) $(BREWRL2) $(INCLUDE) -c -o $@ $^

$(OBJ_DIR)/%.o: ./parser/%.c
	@echo "Compiled ✅ $(CYAN) $^ $(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

$(OBJ_DIR)/%.o: ./expander/%.c
	@echo "Compiled ✅ $(CYAN) $^ $(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

$(OBJ_DIR)/%.o: ./executor/%.c
	@echo "Compiled ✅ $(CYAN) $^ $(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

$(OBJ_DIR)/%.o: ./error/%.c
	@echo "Compiled ✅ $(CYAN) $^ $(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

$(OBJ_DIR)/%.o: ./builtins/%.c
	@echo "Compiled ✅ $(CYAN) $^ $(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJ_DIR)
	@echo "Cleaned ✅ $(GREEN)object Files $(RESET)"

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)
	@echo "Cleaned ✅ $(GREEN)$(NAME) $(RESET)"

re: fclean all

.PHONY: all clean fclean re