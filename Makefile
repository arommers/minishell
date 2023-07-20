# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: arommers <arommers@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/07/20 13:38:03 by arommers      #+#    #+#                  #
#    Updated: 2023/07/20 13:38:34 by arommers      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC		= 	gcc
CFLAGS	=	-Wall -Wextra -Werror
NAME	=	minishell
LIBFT	=	./libft/libft.a
INCLUDE =	-I./includes
SRC 	=	./lexer/lexer.c ./lexer/lex_list.c	\
			./lexer/lex_util.c .lexer//main.c
			
OBJ_DIR = 	obj
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

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)	
	@echo "Compiled with $(BLUE)$(CFLAGS)$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@echo "$(CYAN)-------------------------------------------"
	@echo "	$(NAME) = NOW READY FOR USE!"
	@echo "-------------------------------------------$(RESET)"

$(LIBFT):
	@$(MAKE) -C ./libft

$(OBJ_DIR)/%.o: ./lexer/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiled ✅ $(CYAN) $^ $(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBFT)
	@echo "$(NAME) Cleansed ✅"

fclean: clean
	@$(MAKE) clean -C ./libft
	rm -f $(NAME)
	@echo "$(GREEN) $(NAME) $(RESET) Cleansed ✅"

re: fclean all

.PHONY: all clean fclean re
