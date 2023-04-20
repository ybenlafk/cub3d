# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 21:01:46 by aarbaoui          #+#    #+#              #
#    Updated: 2023/04/20 02:21:44 by aarbaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3d
CC		:= cc
CFLAGS	:= -Iinclude -O2 -Wall -Wextra -Werror -g
HEADERS	:= include/cub3d.h
ifeq ($(shell uname), Linux)
	LIBFT	:= libs/linux/libft.a
	MLX		:= libs/linux/libmlx.a
	LIBS	:= -ldl -lglfw -pthread -lm
else
	LIBFT 	:= libs/osx/libft.a
	MLX		:= libs/osx/libmlx.a
	LIBS	:= -lglfw -L/Volumes/L/.brew/opt/glfw/lib/
endif
SRCS := src/main.c \
		src/gnl/get_next_line.c \
		src/gnl/get_next_line_utils.c \
		src/utils/ft_realloc.c \
		src/parsing/parse.c \
		src/utils/parse_utils.c \

OBJS := $(SRCS:.c=.o)

%.o: %.c include/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) ${LIBFT} -o $(NAME) $(LIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
