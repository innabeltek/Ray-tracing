# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/02 20:23:08 by ibeltek           #+#    #+#              #
#    Updated: 2017/07/04 16:39:44 by ibeltek          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = src/ft_strcmp.c src/key_event.c src/session.c src/initialization.c src/tracer.c src/find_root.c src/sphere.c src/plane.c src/cone.c src/cylinder.c src/colorize.c src/error.c 

OBJ = $(SRC:.c=.o)

HEAD = include/rtv1.h

FLAGS = -Wall -Wextra -Werror

LIB_V = vector

all: $(NAME)

$(NAME): $(OBJ)
	@make -C src/lib_vec/
	@gcc -o $(NAME) -lmlx -framework OpenGL -framework AppKit -lpthread $(OBJ) src/lib_vec/*.o
	@echo "\x1b[93;1;45m--RTv1 has been created--\x1b[0m"
	@echo "\x1b[93;46mUSAGE:\x1b[0m"
	@echo "\x1b[93;3m./RTv1 sphere ||/&& cone ||/&& cylinder ||/&& plane ||/&& plane2 ||/&& plane3\x1b[0m"
	@echo "\x1b[93;3mOR\x1b[0m"
	@echo "\x1b[93;3m./RTv1 scene\x1b[0m"

%.o: %.c
	@gcc $(FLAGS) -c -o  $@ $<

cleanlib:
	@make clean -C src/lib_vec/

fcleanlib:
	@make fclean -C src/lib_vec/

clean: cleanlib
	@rm -f $(OBJ)

fclean:	clean fcleanlib
	@rm -f $(NAME)

re: fclean all
    