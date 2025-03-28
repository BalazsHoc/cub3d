
NAME = cub3D

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
MLXFLAGS = -L$(MINILIBX_PATH) -lmlx_Linux -lXext -lX11 -lm

MINILIBX_PATH = minilibx-linux/

SRCS =	main.c get_next_line.c get_next_line_utils.c

OBJ = $(SRCS:.c=.o)

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	@make -C $(MINILIBX_PATH) all
	@$(CC) $(CFLAGS) $(OBJ) -L$(MINILIBX_PATH) -lmlx_Linux $(MLXFLAGS) -o $(NAME)

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@make -C $(MINILIBX_PATH) clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
