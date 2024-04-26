# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 14:35:38 by tibarbos          #+#    #+#              #
#    Updated: 2024/04/26 15:04:19 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo
CC= cc
CFLAGS= -Wall -Wextra -Werror
RM= rm -rf
SRC= main.c actions.c threads.c extra.c #timetables.c
OBJ= ${SRC:.c=.o}

$(NAME): $(OBJ)
	$(CC) -g $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test:
	make re
	clear
	make clean
	./$(NAME) 5 800 200 200