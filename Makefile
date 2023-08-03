# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: arommers <arommers@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/07/20 13:38:03 by arommers      #+#    #+#                  #
#    Updated: 2023/08/03 17:34:31 by mgoedkoo      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
NAME	=	minishell
LIBFT	=	./libft/libft.a
INCLUDE =	-I./includes
EXE_SRC =	./executor/children.c\
			./executor/cmds_utils.c\
			./executor/executor.c\
			./executor/heredoc.c\
			./executor/pipex.c\
			./executor/redirects.c\
			./executor/run_cmd.c\
			./executor/single_cmd.c
EXP_SRC =	./expander/expand_str.c\
			./expander/expand_utils.c\
			./expander/expand_var.c\
			./expander/quote_utils.c\
			./expander/var_utils.c
PAR_SRC =	./parsing/lexer.c ./parsing/lex_list.c	\
			./parsing/lex_util.c .parsing/main.c	\
			./parsing/lex_del.c ./parsing/parser.c	\
			./parsing/pars_list.c					\
			./parsing/pars_util.c					\
			./parsing/print.c
OBJ_DIR =	obj
EXE_OBJ =	$(addprefix $(OBJ_DIR)/, $(notdir $(EXE_SRC:.c=.o)))
EXP_OBJ =	$(addprefix $(OBJ_DIR)/, $(notdir $(EXP_SRC:.c=.o)))
PAR_OBJ =	$(addprefix $(OBJ_DIR)/, $(notdir $(PAR_SRC:.c=.o)))
BOLD    := \033[1m./SRC/
RED     := \033[31;1m
GREEN   := \033[32;1m
YELLOW  := \033[33;1m
BLUE    := \033[34;1m
MAGENTA := \033[35;1m
CYAN    := \033[36;1m
WHITE   := \033[37;1m
RESET	= \x1b[0m

all: $(NAME)

$(NAME): $(LIBFT) $(EXE_OBJ) $(EXP_OBJ) $(PAR_OBJ)
	@echo "Compiled with $(BLUE)$(CFLAGS)$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(EXE_OBJ) $(EXP_OBJ) $(PAR_OBJ) $(LIBFT) -lreadline
	@echo "$(CYAN)-------------------------------------------"
	@echo "	$(NAME) = NOW READY FOR USE!"
	@echo "-------------------------------------------$(RESET)"

$(LIBFT):
	@$(MAKE) -C ./libft

$(EXE_OBJ): $(OBJ_DIR)/%.o: ./executor/%.c
	mkdir -p $(OBJ_DIR)
	@echo "Compiled ✅ $(CYAN) $^ $(RESET)"
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

$(EXP_OBJ): $(OBJ_DIR)/%.o: ./expander/%.c
	@echo "Compiled ✅ $(CYAN) $^ $(RESET)"
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

$(PAR_OBJ): $(OBJ_DIR)/%.o: ./parsing/%.c
	@echo "Compiled ✅ $(CYAN) $^ $(RESET)"
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	@$(MAKE) clean -C ./libft
	rm -rf $(OBJ_DIR)
	@echo "$(NAME) Cleansed ✅"

fclean: clean
	@$(MAKE) fclean -C ./libft
	rm -f $(NAME)
	@echo "$(GREEN) $(NAME) $(RESET) Cleansed ✅"

re: fclean all

.PHONY: all clean fclean re
