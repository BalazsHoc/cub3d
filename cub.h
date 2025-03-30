#ifndef CUB
# define CUB

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <X11/keysym.h>
// # include "mlx.h"
# include "minilibx-linux/mlx.h"

typedef struct line_s
{
	int		num;
	int		length;
}	t_line;

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
	
}	t_d;


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


# endif