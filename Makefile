# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 14:35:38 by tibarbos          #+#    #+#              #
#    Updated: 2024/04/22 16:59:34 by tibarbos         ###   ########.fr        #
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
	$(CC) $(CFLAGS) $(S_OBJ) ${M_OBJ} $(LFT) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(S_OBJ) $(M_OBJ) $(B_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
