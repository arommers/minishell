# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/10 15:11:23 by mgoedkoo      #+#    #+#                  #
#    Updated: 2023/08/07 10:12:59 by arommers      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 	=	libft.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRC		=	ft_atoi.c ft_bzero.c			\
			ft_calloc.c ft_isalnum.c		\
			ft_isalpha.c ft_isascii.c		\
			ft_isdigit.c ft_isprint.c		\
			ft_itoa.c ft_lstadd_back.c		\
			ft_lstadd_front.c ft_lstclear.c	\
			ft_lstdelone.c ft_lstiter.c		\
			ft_lstlast.c ft_lstmap.c		\
			ft_lstnew.c ft_lstsize.c		\
			ft_memchr.c ft_memcmp.c			\
			ft_memcpy.c ft_memmove.c		\
			ft_memset.c ft_putchar_fd.c		\
			ft_putendl_fd.c ft_putnbr_fd.c	\
			ft_putstr_fd.c ft_split.c		\
			ft_strchr.c ft_strdup.c			\
			ft_striteri.c ft_strjoin.c		\
			ft_strlcat.c ft_strlcpy.c		\
			ft_strlen.c ft_strmapi.c		\
			ft_strncmp.c ft_strnstr.c		\
			ft_strrchr.c ft_strtrim.c		\
			ft_substr.c ft_tolower.c		\
			ft_toupper.c get_next_line.c	\
			ft_printf/ft_printf.c			\
			ft_printf/va_deciders.c			\
			ft_printf/va_makers.c			\
			ft_printf/va_printers.c
OBJ_DIR	=	obj
OBJ		=	$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

MESSAGE = 0
YELLOW  := \033[33;1m
BLUE    := \033[34;1m
RESET	= \x1b[0m

all: $(NAME)

$(NAME):
	@if [ $(MESSAGE) -eq 0 ]; then									\
		echo "$(YELLOW)----------------------------------------";		\
		echo "           $(NAME) = STARTED";						\
		echo "----------------------------------------$(RESET)";	\
		export MESSAGE=1;											\
	fi
	@$(MAKE) compile

compile: $(OBJ)
	@echo "Compiled with $(BLUE)$(CFLAGS)$(RESET)"
	@ar -rcs $(NAME) $^
	@echo "$(YELLOW)----------------------------------------"
	@echo "    $(NAME) = NOW READY FOR USE!"
	@echo "----------------------------------------$(RESET)"

$(OBJ_DIR)/%.o: ./%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiled ✅ $(YELLOW) $^ $(RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $^

$(OBJ_DIR)/%.o: ./ft_printf/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiled ✅ $(YELLOW) $^ $(RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@rm -rf $(OBJ_DIR)

fclean:
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re