# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 14:35:38 by tibarbos          #+#    #+#              #
#    Updated: 2024/08/04 14:55:59 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

# Compiler && Tools
CC= cc
CFLAGS= -Wall -Wextra -Werror
SAN= -fsanitize=thread
RM= rm -rf

# Output colors
RED= \e[31m
GREEN= \e[32m
BLUE= \e[34m
WHITE= \e[37m

# Source && Object Files
SRC= ./src/main.c ./src/actions.c ./src/threads.c \
	./src/extra.c ./src/timetables.c ./src/reaper.c
OBJDIR= ./obj
OBJ= $(SRC:%.c=$(OBJDIR)/%.o)

# Includes
LIB= -pthread

.PHONY: all test clean fclean re

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)
	@echo "$(BLUE)philo: $(GREEN)program compiled$(WHITE)"

all: $(NAME)

test: $(OBJ)
	@$(CC) $(CFLAGS) $(SAN) $(OBJ) $(LIB) -o $(NAME)
	@echo "$(BLUE)philo: $(GREEN)thread test program compiled$(WHITE)"

clean:
	@$(RM) $(OBJDIR)
	@echo "$(BLUE)philo: $(RED)object files removed$(WHITE)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BLUE)philo: $(RED)library and object files removed$(WHITE)"

re: fclean all