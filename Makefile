
NAME = cub3D

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
# MLXFLAGS = -lmlx -lXext -lX11 -lm

SRCS =	main.c get_next_line.c get_next_line_utils.c

OBJ = $(SRCS:.c=.o)

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJ) $(LIBFT) $(FT_PRINTF) $(GET_NEXT_LINE) -o $(NAME)

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
