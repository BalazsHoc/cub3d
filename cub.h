/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:11:08 by bhocsak           #+#    #+#             */
/*   Updated: 2025/05/01 13:11:10 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define BUFFER_SIZE 16
# define TEXTURE_SIZE 1024

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

/******************** 
 CONTROLL CENTER 
 *********************/

# define WIDTH 1280
# define HEIGHT 720
# define FOV 60
# define WALL_RESIZE 9
# define MINI_MAP 1
# define MINI_PLAYER 10
# define MINI_WALL 15
# define MINI_PLAYER_C 16711935
# define MINI_WALL_C 8421504
# define MAP_SIZE 20

# define WALL 10
# define SPEED 0.3
# define R_SPEED 0.015

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

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
# include "mlx.h"
// # include "minilibx-linux/mlx.h"

typedef struct screen_s
{
	void				*img;
	void				*addr;
	int					width;
	int					height;
	int					bpp;
	int					line_length;
	int					edian;
}	t_screen;

typedef struct texture_s
{
	void				*img;
	void				*addr;
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

typedef struct player_s
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

typedef struct data_s
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
	char				**buf_arr;
	struct line_s		*line;
	int					width;
	int					heigth;
	int					f;
	int					c;
	void				*window;
	void				*mlx_ptr;
	double				pi;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					draw_y;
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
	int					tex_x;
	int					tex_y;
	struct texture_s	screen_img[1];
	struct player_s		*player;
	struct texture_s	textures[4];
}	t_data;

void		ft_printe(char *str);

//	srcs/get_next_line/get_next_line.c
void		*gnl_calloc(size_t nmemb, size_t size);
char		*gnl_join_free(char *static_buf, char *buffer);
char		*gnl_join_buffer(char *line, char *buffer);
char		*get_next_line(int fd);

//	srcs/get_next_line/get_next_line_utils.c
void		gnl_free(char **ptr);
int			gnl_strlen(char *str);
int			gnl_newline(char *str);
char		*gnl_strcpy(char *str);
char		*gnl_fromnl(char *str);

//	srcs/libft/libft_1.c
void		*ft_calloc(t_data *d, size_t nmemb, size_t size);
char		*ft_itoa(int n, t_data *data);
long long	ft_atoi(const char *nptr);
char		*ft_strdup(t_data *d, const char *s);

//	srcs/libft/libft_2.c
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(t_data *d, char const *s, unsigned int start, size_t l);
int			ft_strlen(const char *str);
char		*ft_strchr(const char *s, int c);
char		*ft_strtrim(t_data *d, char const *s1, char const *set);

//	srcs/libft/libft_3.c
void		ft_bzero(void *s, size_t n);

//	srcs/rgb.c
void		cut_num(t_data *d, char *color, int i, int loop);
int			to_rgb(t_data *d);
void		check_rgb(t_data *d, char *color, int *to_store);

//	srcs/sort_data.c
void		reading_data(t_data *d, char **argv);

//	srcs/map.c
void		print_map(t_data *d);
void		check_walls(t_data *d, int y, int x);
void		check_map(t_data *d, int pos, int x, int y);
void		save_map(t_data *d, char *line);
int			map_name(char *map_name);

//	srcs/control.c
int			handle_click_x(t_data *d);
int			key_press(int key, t_data *d);
int			key_release(int key, t_data *d);

//	srcs/movement.c
void		find_player(t_data *d);
void		set_angle(t_data *d, int x, int y);
void		move_player_coor(t_data *d);

//	srcs/is.c
int			only_whitespace(char *color);
int			is_white_space(char c);
int			is_wall(t_data *d, double new_x, double new_y);

//	srcs/texture_1.c
void		convert_texture(t_data *d, int type, char *texture, int i);
void		draw_textures(t_data *d, double distance, int cur_col_x, int type);

//	srcs/texture_2.c
void		set_tex_x(t_data *d, int type);
void		setup_xy(t_data *d);

//	srcs/raycasting.c
void		raycast(t_data *d);

//	srcs/minimap.c
void		draw_miniplayer(t_data *d, int pixel_x, int pixel_y, int size);
void		delete_miniplayer(t_data *d, int pixel_x, int pixel_y, int size);
void		draw_square(t_data *d, int pixel_x, int pixel_y, int size);
void		delete_square(t_data *d, int pixel_x, int pixel_y, int size);
void		draw_mini_map(t_data *d);

//	srcs/displaying.c
void		put_pixel(t_data *d, int x, int y, int color);
int			drawing(t_data *d);
void		displaying(t_data *d);

//	srcs/init_1.c
void		init_dblptr(char **dbptr, int size);
void		init_rays(t_data *d);
void		init_texture(t_data *d);
void		init_data(t_data *d);
void		init_player(t_data *d);

//	srcs/init_2.c
void		init_draw_var(t_data *d);
void		init_line_struct(t_data *d);

//	srcs/free.c
void		free_colors(char **dbptr, int size);
void		free_map(char **map);
void		free_str(char *str);
void		free_mlx(t_data *d);
void		free_player(t_data *d);

//	srcs/exit.c
void		error_clean(t_data *d);
void		exit_clean(t_data *d);

#endif
