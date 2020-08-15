# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jslave <jslave@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/12 21:32:49 by jslave            #+#    #+#              #
#    Updated: 2019/11/19 17:38:22 by jslave           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = lem-in

HEADER = inc/lemin.h

LIBFT = libft

LIBFT_INCLUDES = libft/includes

INCLUDES = inc/

FLAGS =

SRC1 = src/*.c *.c

OUT1 = $(SRC1:%.c=%.o)

all: $(NAME1) $(NAME2)

$(NAME1): $(OUT1)
	make -C $(LIBFT)
	gcc $(FLAGS) -o $(NAME1) $(OUT1) -L $(LIBFT) -lft
%.o: %.c $(HEADER)
	gcc $(FLAGS) -I $(LIBFT_INCLUDES) -I $(INCLUDES) -o $@ -c $<

clean:
	/bin/rm -f $(OUT1)
	make -C $(LIBFT) clean

fclean: clean
	/bin/rm -f $(NAME1)
	make -C $(LIBFT) fclean

re: fclean all
