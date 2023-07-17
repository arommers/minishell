# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/09 17:38:57 by mgoedkoo      #+#    #+#                  #
#    Updated: 2023/07/17 14:53:23 by arommers      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		minishell
SRCS =		children.c\
			main.c\
			pipex.c\
			run_cmd.c\
			utils.c
OBJS =		$(SRCS:%.c=build/%.o)
LIBFT =		libft/
# RL_DIR =	$(shell brew --prefix readline)
# RL_LIB =	-L $(RL_DIR)/lib -lreadline -lhistory 
CFLAGS +=	-Wall -Wextra -Werror

all: $(NAME)

clean:
	@make clean -C $(LIBFT)
	rm -f $(OBJS)
	rm -df build
	@echo "$(NAME) cleaned up nicely"

fclean: clean
	@make fclean -C $(LIBFT)
	rm -f $(NAME)
	@echo "$(NAME) fcleaned up nicely"

re: fclean all

$(NAME): $(OBJS)
	@echo "the $(NAME) o-files are ready"
	@make all -C $(LIBFT)
	cc $(C-FlAGS) -o $(NAME) $^ -L $(LIBFT) -lft
	@echo "$(NAME) is ready"

$(OBJS): build/%.o : %.c
	@mkdir -p build
	cc $(CFLAGS) -c $< -o $@