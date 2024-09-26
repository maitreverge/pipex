# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flverge <flverge@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/18 17:11:27 by flverge           #+#    #+#              #
#    Updated: 2024/09/26 13:28:33 by flverge          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program names
NAME				:= pipex
NAME_BONUS			:= pipex_bonus

# Compiler options
CC 					:= cc

# Flags
# CFLAGS 				:= -Wall -Wextra -Werror
CFLAGS 				:= -Wall -Wextra -Werror -g  # debug

# Libft
LIBFT_NAME			:= libmaster.a
LIBFT_PATH			:= libft/
LIBFT				:= $(LIBFT_PATH)$(LIBFT_NAME)

# Mandatory Source Files
DIR_SRC_MANDATORY	:= mandatory/src
SRC_MANDATORY		:= $(wildcard $(DIR_SRC_MANDATORY)/*.c)

# Mandatory Objects
DIR_OBJ_MANDATORY	:= ./mandatory/obj
OBJ_MANDATORY		:= $(SRC_MANDATORY:$(DIR_SRC_MANDATORY)/%.c=$(DIR_OBJ_MANDATORY)/%.o)

# Bonus Source Files
DIR_SRC_BONUS		:= bonus/src
SRC_BONUS			:= $(wildcard $(DIR_SRC_BONUS)/*.c)

# Bonus Objects
DIR_OBJ_BONUS	:= ./bonus/obj
OBJ_BONUS		:= $(SRC_BONUS:$(DIR_SRC_BONUS)/%.c=$(DIR_OBJ_BONUS)/%.o)

# Includes
INC_MANDATORY		=	-I ./mandatory/includes
INC_BONUS			=	-I ./bonus/includes

# Colors
RESET				:= \033[0m
BOLD				:= \033[1m
RED					:= \033[91m
GREEN				:= \033[92m
YELLOW				:= \033[33m
ORANGE				:= \033[93m
BLUE				:= \033[94m


all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(NAME_BONUS)

# Create object directories if they don't exist
$(DIR_OBJ_MANDATORY):
	@mkdir -p $(DIR_OBJ_MANDATORY)

$(DIR_OBJ_BONUS):
	@mkdir -p $(DIR_OBJ_BONUS)

# Compile mandatory object files
$(DIR_OBJ_MANDATORY)/%.o: $(DIR_SRC_MANDATORY)/%.c | $(DIR_OBJ_MANDATORY)
	@$(CC) $(CFLAGS) $(INC_MANDATORY) -c $< -o $@

# Compile bonus object files
$(DIR_OBJ_BONUS)/%.o: $(DIR_SRC_BONUS)/%.c | $(DIR_OBJ_BONUS)
	@$(CC) $(CFLAGS) $(INC_BONUS) -c $< -o $@

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
	@echo "$(BOLD)$(GREEN)🚀      Pipex fully compiled, ready to use       🚀$(RESET)"
	@echo "\n"

# Bonus rule
$(NAME_BONUS): $(OBJ_BONUS)
	@echo "$(BOLD)$(RED)🛠️      Compiling pipex $(YELLOW)✨ BONUS ✨    🛠️$(RESET)"
	@echo "\n"
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(INC_BONUS) -o $(NAME_BONUS)
	@echo "$(BOLD)🚀      $(GREEN)Pipex $(YELLOW)✨ BONUS ✨ $(GREEN)fully compiled, ready to use       🚀$(RESET)"
	@echo ""
	@echo "$(BOLD)		Usage Bonus : $(RESET)"
	@echo ""
	@echo "$(BOLD) $(YELLOW) ✨ BONUS 1 ✨ $(RESET) ./pipex_bonus  file1 cmd1 cmd2 cmd3 ... cmdn file2 $(RESET)"
	@echo "$(BOLD) $(ORANGE) ✨ BONUS 2 ✨ $(RESET) ./pipex_bonus  here_doc LIMITER cmd cmd1 file $(RESET)"

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

re: fclean all

rebonus: fclean bonus

# Rajouter .PHONY