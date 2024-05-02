# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 14:35:38 by tibarbos          #+#    #+#              #
#    Updated: 2024/05/02 13:10:57 by tibarbos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo
CC= cc
CFLAGS= -Wall -Wextra -Werror #-fsanitize=thread
RM= rm -rf
SRC= main.c actions.c threads.c extra.c timetables.c
OBJ= ${SRC:.c=.o}
LIB= -pthread

$(NAME): $(OBJ)
	$(CC) -g $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

#test:
#	make re
#	clear
#	make clean
#	./$(NAME) 4 310 200 100
#0	./$(NAME) 5 800 200 200
#0	./$(NAME) 5 800 200 200 7 (400*7 = 2600, 2800)
#0	./$(NAME) 4 410 200 200
#0	./$(NAME) 4 410 200 200 7 (400*7 = 2600, 2800)
#1	./$(NAME) 4 310 200 100