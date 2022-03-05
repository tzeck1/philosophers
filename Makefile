# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tom <tom@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 00:09:38 by tom               #+#    #+#              #
#    Updated: 2022/03/04 21:01:42 by tom              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# EXECUTABLE
NAME = ./philo

# FLAGS
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# COLORS
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

# PATHS
SRC_PATH = ./src/
OBJ_PATH = ./obj/
UTILS_PATH = ./src/

# SOURCES
SRC =	$(SRC_PATH)main.c $(SRC_PATH)utils.c \
		$(SRC_PATH)input.c $(SRC_PATH)philos.c

# OBJECTS
OBJ = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))

# RULES
all: $(NAME)
	@sleep 0.15
	@echo $(B)"         __     __ __                           __                      "$(X)
	@sleep 0.15
	@echo $(B)" .-----.|  |--.|__|  |.-----.-----.-----.-----.|  |--.-----.----.-----. "$(X)
	@sleep 0.15
	@echo $(B)" |  _  ||     ||  |  ||  _  |__ --|  _  |  _  ||     |  -__|   _|__ --| "$(X)
	@sleep 0.15
	@echo $(B)" |   __||__|__||__|__||_____|_____|_____|   __||__|__|_____|__| |_____| "$(X)
	@sleep 0.15
	@echo $(B)" |__|                                   |__|                            "$(X)
	@sleep 0.15
	@printf "\n\n"

$(OBJ_PATH)%.o :$(SRC_PATH)%.c
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p $(dir $@)
	@sleep 0.2
	@printf $(UP)$(CUT)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo $(G)Finished [$@]$(X)
	@sleep 0.2
	@printf $(UP)$(CUT)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo $(G)Finished [$(NAME)]$(X)

clean:
	@if [ -d "$(OBJ_PATH)" ]; then \
			rm -f -r $(OBJ_PATH); \
			echo $(R)Cleaning" "[$(OBJ) $(OBJ_PATH)]$(X); else \
			echo "No objects to remove."; \
	fi;

fclean: clean
	@if [ -f "$(NAME)" ]; then \
			rm -f $(NAME); \
			echo $(R)Cleaning" "[$(NAME)]$(X);else \
			echo "No executable to remove."; \
	fi;

re: fclean all

.PHONY: all, clean, fclean, re
