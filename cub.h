#ifndef CUB
# define CUB

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8

# define WIDTH 1280
# define HEIGHT 720


# define SIZE 10
# define BLOCK 60

# define SPEED 0.15
# define SENSITIVITY 0.005

# define RAYSPRAD 50

# define W 119
# define A 97
# define S 115
# define D 100
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <math.h>
// # include "mlx.h"
# include "minilibx-linux/mlx.h"

typedef struct line_s
{
	int		num;
	int		length;
}	t_line;

typedef struct player_s
{
	float			x;
	float			y;
	bool			up;
	bool			down;
	bool			left;
	bool			right;

	int				map_x;
	int				map_y;

	double			angle;
}	t_player;

typedef struct data_s
{
	char			**map;

	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*floor;
	char			*ceiling;

	char			*buf;

	char			*colors[3];
	char			*textures[4];

	char			*read_buf;
	struct line_s	*line;

	int				width;
	int				heigth;
	int				f;
	int				c;

	void			*window;
	void			*mlx_ptr;
	void			*img;

	// char			*addr;

	// int				bpp;
	// int				size_line;
	// int				endian;

	double			pi;

	struct player_s	*player;
	
}	t_data;



void	free_str(char *str);
void	ft_printe(char *str);

void	*gnl_calloc(size_t nmemb, size_t size);
char	*gnl_join_free(char *static_buf, char *buffer);
char	*gnl_join_buffer(char *line, char *buffer);
char	*reading(int fd, char *static_buf);
char	*get_next_line(int fd);

void	gnl_free(char **ptr);
int		gnl_strlen(char *str);
int		gnl_newline(char *str);
char	*gnl_strcpy(char *str);
char	*gnl_fromnl(char *str);

void	draw_map(t_data *d);


# endif