# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 14:35:38 by tibarbos          #+#    #+#              #
#    Updated: 2024/07/18 17:38:14 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo
CC= cc
CFLAGS= -Wall -Wextra -Werror -fsanitize=thread
RM= rm -rf
SRC= ./src/main.c ./src/actions.c ./src/threads.c \
	./src/extra.c ./src/timetables.c ./src/reaper.c
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