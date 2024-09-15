# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flverge <flverge@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/18 17:11:27 by flverge           #+#    #+#              #
#    Updated: 2024/09/15 12:54:52 by flverge          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program names
NAME		:= pipex
NAME_BONUS	:= pipex_bonus

# Compiler options
CC := cc

# Flags
CFLAGS := -Wall -Wextra -Werror

# libft
LIBFT_NAME	:= libmaster.a
LIBFT_PATH	:= libft/
LIBFT		:= $(LIBFT_PATH)$(LIBFT_NAME)

# Mandatory Source Files
DIR_SRC_MANDATORY	:= mandatory/src
SRC_MANDATORY		:= $(wildcard $(DIR_SRC_MANDATORY)/*.c)

# Bonus Source Files
DIR_SRC_BONUS	:= bonus/src
SRC_BONUS		:= $(wildcard $(DIR_SRC_BONUS)/*.c)

# Objects Files
DIR_OBJ_MANDATORY	:= ./mandatory/obj
DIR_OBJ_BONUS		:= ./bonus/obj
OBJ_MANDATORY		:= ${SRC_MANDATORY:.c=.o}

# Includes
INC_MANDATORY	:=	-I ./mandatory/includes
INC_BONUS		:=	-I ./bonus/includes

# Colors
RESET := \033[0m
BOLD := \033[1m
RED := \033[91m
GREEN := \033[92m
YELLOW := \033[33m
ORANGE := \033[93m
BLUE := \033[94m


all: $(LIBFT) $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -sC $(LIBFT_PATH)
	@echo "\n"
	@echo "$(BOLD)$(BLUE)-----------------------$(RESET)"
	@echo "\n"	

# Madatory Rule
$(NAME): $(OBJ_MANDATORY)
	@echo "$(BOLD)$(RED)🛠️      Compiling pipex    🛠️$(RESET)"
	@echo "\n"
	@$(CC) $(CFLAGS) $(OBJ_MANDATORY) $(LIBFT) $(INC_MANDATORY) -o $(NAME)
	@echo "$(BOLD)$(GREEN)✅✅      Pipex fully compiled, ready to use       ✅✅$(RESET)"
	@echo "\n"

# Exec Bonus
$(NAME_BONUS): $(OBJ_BONUS)
	@echo "$(BOLD)$(RED)🛠️      Compiling pipex bonus    🛠️$(RESET)"
	@echo "\n"
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(INC_BONUS) -o $(NAME_BONUS)
	@echo "$(BOLD)$(GREEN)✅✅      Pipex fully compiled, ready to use       ✅✅$(RESET)"
	@echo "\n"

clean:
	@make clean -sC $(LIBFT_PATH)
	@rm -rf $(DIR_OBJ_MANDATORY)
	@rm -rf $(DIR_OBJ_BONUS)
	@echo "$(BOLD)$(ORANGE)🌀     Cleaned .o pipex's files   🌀$(RESET)"

fclean: clean
	@make fclean -sC $(LIBFT_PATH)
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@echo "$(BOLD)$(ORANGE)🌀     Cleaned pipex exec       🌀$(RESET)"

bonus: $(LIBFT) $(NAME_BONUS)

re: fclean all

rebonus: fclean bonus

# Rajouter .PHONY