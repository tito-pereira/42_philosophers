# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 14:35:38 by tibarbos          #+#    #+#              #
#    Updated: 2024/05/04 18:50:25 by tibarbos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo
CC= cc
CFLAGS= -Wall -Wextra -Werror #-fsanitize=thread
RM= rm -rf
SRC= main.c actions.c threads.c extra.c timetables.c reaper.c
OBJ= ${SRC:.c=.o}
LIB= -pthread

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all