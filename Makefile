
NAME = cub3D

CC = cc
CFLAGS = -Wall -Werror -Wextra
# MLXFLAGS = -lmlx -lXext -lX11 -lm -L$(MINILIBX_PATH)    
MLXFLAGS = -lmlx -lXext -lX11 -lm

MINILIBX_PATH = minilibx-linux/

SRCS =	main.c\
		srcs/get_next_line/get_next_line.c srcs/get_next_line/get_next_line_utils.c\
		srcs/libft/libft_1.c srcs/libft/libft_2.c srcs/libft/libft_3.c\
		srcs/init_1.c srcs/init_2.c\
		srcs/free.c srcs/exit.c\
		srcs/rgb.c\
		srcs/sort_data.c\
		srcs/map.c\
		srcs/control.c\
		srcs/movement.c\
		srcs/is.c\
		srcs/raycasting.c\
		srcs/minimap.c\
		srcs/displaying.c\
		srcs/texture_1.c srcs/texture_2.c


OBJ = $(SRCS:.c=.o)

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
#	@make -C $(MINILIBX_PATH) all
	@$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)
#	@$(CC) $(CFLAGS) $(OBJ) -L$(MINILIBX_PATH) -lmlx_Linux $(MLXFLAGS) -o $(NAME)

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
#	@make -C $(MINILIBX_PATH) clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
