# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibeltek <ibeltek@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/13 16:34:37 by ibeltek           #+#    #+#              #
#    Updated: 2017/05/17 13:56:59 by ibeltek          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = vector

SRC = ./subtract.c ./dot_prod.c ./scale.c ./add.c ./vec_len.c ./angle.c ./vec_dir.c ./equal.c

OBJ = $(SRC:.c=.o)

HEAD = ./vector.h

WWW = -Wall -Werror -Wextra

ARRC = ar rc

all: $(NAME)

$(NAME): $(OBJ)
	@ $(ARRC) $(NAME) $(OBJ)
	@ ranlib $(NAME)

%.o: %.c $(HEAD)
	@gcc $(WWW) -c -o $@ $< 

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME) 

re: fclean all
