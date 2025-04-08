# ifndef CUB
# define CUB

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8

# define TEXTURE_SIZE 1024

/******************** 
	CONTROLL CENTER 
*********************/

# define WIDTH 1280
# define HEIGHT 720
# define FOV 75
# define WALL_RESIZE 9.5
# define MINI_MAP 1
# define MINI_PLAYER 10
# define MINI_WALL 15

# define WALL 10
# define SPEED 0.3
# define R_SPEED 0.025
# define SENSITIVITY 0.005

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

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

typedef struct texture_s
{
	void				*img;
	void				*addr;
	int					pixel[64][64];
	int					width;
	int					height;
	int					bpp;
	int					line_length;
	int					edian;
}	t_texture;

typedef struct line_s
{
	int					num;
	int					length;
}	t_line;

typedef struct	player_s
{
	double				x;
	double				y;
	bool				up;
	bool				down;
	bool				left;
	bool				right;
	bool				turn_l;
	bool				turn_r;

	int					map_x;
	int					map_y;

	double				angle;
}	t_player;

typedef struct	data_s
{
	char				**map;

	char				*north;
	char				*south;
	char				*west;
	char				*east;
	char				*floor;
	char				*ceiling;

	char				*buf;

	char				*colors[3];

	char				*read_buf;
	struct line_s		*line;

	int					width;
	int					heigth;
	int					f;
	int					c;

	void				*window;
	void				*mlx_ptr;

	double				pi;


	int					mx;
	int					my;
	double				r_angle;
	double				rx;
	double				ry;
	int					step_x;
	int					step_y;
	double				ray_dir_x;
	double				ray_dir_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				side_dist_x;
	double				side_dist_y;
	bool				y_wall;



	struct player_s		*player;
	struct texture_s	textures[4];
	
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

void	draw_mini_map(t_data *d);


# endif