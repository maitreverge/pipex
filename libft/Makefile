# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flverge <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 10:22:50 by flverge           #+#    #+#              #
#    Updated: 2023/11/20 09:14:55 by flverge          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmaster.a

OBJ = libft/src/*.o ft_printf/src/*.o get_next_line/src/*.o

LIBS = $(NAME) libft/*.a ft_printf/*.a get_next_line/*.a

RESET = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[33m

all: $(NAME)

projects:
	@echo "$(BOLD)$(RED)🛠️      Compiling libft      🛠️$(RESET)"
	@make -s -C libft/
	@make -s -C ft_printf/
	@make -s -C get_next_line/

$(NAME): projects
	@ar -rcs $(NAME) libft/src/*.o ft_printf/src/*.o get_next_line/src/*.o
	@echo "$(BOLD)$(GREEN)😎      Libft Compiled      😎$(RESET)"

clean:
	@rm -f $(OBJ)
	@echo "$(BOLD)$(YELLOW)🧹     Cleaned .o libft files     🧹$(RESET)"

fclean: clean
	@rm -f $(LIBS)
	@echo "$(BOLD)$(YELLOW)🧹     Cleaned libmaster.a        🧹$(RESET)"

re: fclean all