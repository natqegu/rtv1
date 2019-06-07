# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/29 13:23:34 by nnovikov          #+#    #+#              #
#    Updated: 2019/03/29 13:23:38 by nnovikov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

DIR = objects

PATH_INC = ./libft/includes/

CC = gcc

FLAGS = -Wall -Wextra -Werror -O3

SRC_C =	main.c 

SRC_O = $(addprefix objects/,$(SRC_C:.c=.o))

$(DIR)/%.o: %.c 
	gcc $(FLAGS) -o $@ -c $<

all: $(NAME)

$(DIR):
	mkdir -p $(DIR)

$(NAME): $(DIR) $(SRC_O)
	make -C libft/
	$(CC) -o $(NAME) $(SRC_O) -lm -L libft/ -lft -lmlx -framework OpenGL -framework AppKit

clean:
	make -C libft/ clean
	/bin/rm -rf $(DIR)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all
