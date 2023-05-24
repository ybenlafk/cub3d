NAME	:= cub3D
CC		:= cc
CFLAGS	:= -Iinclude -Ofast -Wall -Wextra -Werror
HEADERS	:= include/cub3d.h
LIBFT	:= libs/libft.a
MLX		:= libs/libmlx.a
# LIBS	:= -lglfw -L/Volumes/L/.brew/opt/glfw/lib
LIBS	:= -lglfw -L/Users/ybenlafk/.brew/opt/glfw/lib/
SRCS := srcs/main.c \
		srcs/parsing/parse.c \
		srcs/engine/raycast.c \
		srcs/engine/player.c \
		srcs/engine/skybox.c \
		srcs/utils/is_map.c \
		srcs/utils/get_map_size.c \
		srcs/utils/ft_realloc.c \
		srcs/utils/gnl/get_next_line_utils.c \
		srcs/utils/free_all.c \
		srcs/utils/ft_strcmp.c \
		srcs/utils/gnl/get_next_line.c \
		srcs/utils/get_step.c \
		srcs/utils/get_rgba.c \
		srcs/engine/minimap.c \
		srcs/utils/mlx_draw_line.c \
		srcs/utils/get_dem.c \


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