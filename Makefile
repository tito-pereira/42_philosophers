# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 14:35:38 by tibarbos          #+#    #+#              #
#    Updated: 2023/12/27 17:46:13 by tibarbos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= pipex
CC= cc
CFLAGS= -Wall -Wextra -Werror
RM= rm -rf
SRC= ./mandatory/m_free.c \
	./mandatory/m_in_out.c ./mandatory/m_proc.c ./mandatory/m_which.c
MAN= ./mandatory/m_main.c
BON= ./extra/main_bonus.c ./extra/proc_bonus.c
S_OBJ= ${SRC:.c=.o}
M_OBJ= ${MAN:.c=.o}
B_OBJ= ${BON:.c=.o}
LIB= ./libft/libft.a
LFT= -L./libft -lft

$(NAME): $(S_OBJ) ${M_OBJ}
	make -C ./libft
	$(CC) $(CFLAGS) $(S_OBJ) ${M_OBJ} $(LFT) -o $(NAME)

all: $(NAME)

clean:
	cd ./libft && make clean
	$(RM) $(S_OBJ) $(M_OBJ) $(B_OBJ)

fclean: clean
	cd ./libft && make fclean
	$(RM) $(NAME)

re: fclean all
	cd ./libft && make re

bonus:	fclean $(S_OBJ) $(B_OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) $(S_OBJ) $(B_OBJ) $(LFT) -o $(NAME)