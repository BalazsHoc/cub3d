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
// # include "mlx.h"
// # include <X11/keysym.h>

typedef struct data_s
{
	char	**map;
	char	**db_buf;

	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	char	*ceiling;

	char	*read_buf;
	char	*gnl_buf;
}	t_d;

void	free_str(char *str);
void	ft_printe(char *str);

void	*gnl_calloc(size_t nmemb, size_t size);
char	*gnl_join_free(char *static_buf, char *buffer);
char	*gnl_join_buffer(char *line, char *buffer);
char	*reading(int fd, char *static_buf);
char	*get_next_line(int fd, t_d *data);

void	gnl_free(char **ptr);
int		gnl_strlen(char *str);
int		gnl_newline(char *str);
char	*gnl_strcpy(char *str);
char	*gnl_fromnl(char *str);


#endif