# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnovikov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/24 13:04:38 by nnovikov          #+#    #+#              #
#    Updated: 2018/11/29 14:37:40 by nnovikov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -Wall -Werror -Wextra -c
INCLUDES = -I$(HEADERS_DIRECTORY)
HEADERS_LIST = libft.h\
	get_next_line.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))
SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memccpy.c\
	ft_memmove.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_strlen.c\
	ft_strdup.c\
	ft_strcpy.c\
	ft_strncpy.c\
	ft_strcat.c\
	ft_abs.c\
	ft_strncat.c\
	ft_strlcat.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strstr.c\
	ft_strnstr.c\
	ft_strcmp.c\
	ft_strncmp.c\
	ft_atoi.c\
	ft_isalpha.c\
	ft_isdigit.c\
	create_dot.c\
	create_vec.c\
	add_vec.c\
	new_rgb.c\
	substract_vec.c\
	multiply_vec.c\
	cross_vec.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_memalloc.c\
	ft_memdel.c\
	ft_strnew.c\
	ft_strdel.c\
	swap.c\
	is_char_there.c\
	ft_strclr.c\
	ft_striter.c\
	ft_striteri.c\
	ft_strmap.c\
	ft_strmapi.c\
	ft_strequ.c\
	ft_strnequ.c\
	ft_strsub.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_strsplit.c\
	ft_itoa.c\
	ft_putchar.c\
	ft_putstr.c\
	ft_putendl.c\
	ft_putnbr.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_lstnew.c\
	ft_lstdelone.c\
	ft_lstdel.c\
	ft_lstadd.c\
	ft_lstiter.c\
	ft_lstmap.c\
	ft_isupper.c\
	ft_islower.c\
	ft_isspace.c\
	ft_isblank.c\
	ft_strnlen.c\
	ft_strndup.c\
	ft_lstaddback.c\
	ft_strlwr.c\
	ft_strupr.c\
	ft_strrev.c\
	ft_strchrs.c\
	ft_strsubchr.c\
	dot.c \
	normalize.c \
	discriminant.c \
	get_next_line.c
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))
OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDES) $< -o $@

clean:
	@rm -rf $(OBJECTS_DIRECTORY)

fclean: clean
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all