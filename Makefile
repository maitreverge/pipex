# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flverge <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/18 17:11:27 by flverge           #+#    #+#              #
#    Updated: 2023/12/25 12:10:08 by flverge          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = pipex

# Compiler options
CC = cc

# Valgrind flag
# CFLAGS = -Wall -Wextra -Werror -g

# Asan flag
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

# libft
LIBFT_NAME = libmaster.a
LIBFT_PATH = my_42_libft/
LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)

# pipex files
SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := ${SRC:.c=.o}

# Includes
INC =	-I ./includes/

# Colors
RESET = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[33m
ORANGE = \033[93m
BLUE = \033[94m


all: $(LIBFT) $(NAME)

# remettre les flags
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -sC $(LIBFT_PATH)
	@echo "\n"
	@echo "$(BOLD)$(BLUE)-----------------------$(RESET)"
	@echo "\n"	

# remettre flags
$(NAME): $(OBJ)
	@echo "$(BOLD)$(RED)🛠️      Compiling pipex    🛠️$(RESET)"
	@echo "\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INC) -o $(NAME)
	@echo "$(BOLD)$(GREEN)✅✅      Pipex fully compiled, ready to use       ✅✅$(RESET)"
	@echo "\n"

clean:
	@make clean -sC $(LIBFT_PATH)
	@rm -f $(OBJ)
	@echo "$(BOLD)$(ORANGE)🌀     Cleaned .o pipex's files   🌀$(RESET)"

fclean: clean
	@make fclean -sC $(LIBFT_PATH)
	@rm -f $(NAME)
	@echo "$(BOLD)$(ORANGE)🌀     Cleaned pipex exec       🌀$(RESET)"

bonus: all

re: fclean all
