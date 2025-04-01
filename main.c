/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:06:16 by bhocsak           #+#    #+#             */
/*   Updated: 2025/03/25 13:06:19 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_printe(char *str)
{
	while (*str)
		write(2, str++, 1);
}

void	print_map(t_data *d)
{
	int	i;

	i = -1;
	while(d->map[++i])
		printf("%s", d->map[i]);
	printf("\n");
}

void	free_colors(char **dbptr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free_str(dbptr[i]);
		i++;
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map || !map[i])
		return ;
	while (map[i])
	{
		free_str(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	free_str(char *str)
{
	
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	free_mlx(t_data *d)
{
	if (d->img)
		mlx_destroy_image(d->mlx_ptr, d->img);
	d->img = NULL;
	if (d->window)
		mlx_destroy_window(d->mlx_ptr, d->window);
	d->window = NULL;
	if (d->mlx_ptr)
	{
		mlx_destroy_display(d->mlx_ptr);
		free(d->mlx_ptr);
		d->mlx_ptr = NULL;
	}
}

void	free_player(t_data *d)
{
	if (d->player)
	{
		free(d->player);
		d->player = NULL;
	}
}

void	error_clean(t_data *d)
{
	if (d)
	{
		free_map(d->map);
		free_str(d->north);
		free_str(d->south);
		free_str(d->west);
		free_str(d->east);
		free_str(d->floor);
		free_str(d->ceiling);
		free_str(d->buf);
		free_colors(d->colors, 3);
		free_colors(d->textures, 4);
		free_str(d->read_buf);
		get_next_line(-1);
		free_str((char *)d->line);
		free_mlx(d);
		free_player(d);
		free(d);
		d = NULL;
	}
	exit(1);
}

void	exit_clean(t_data *d)
{
	if (d)
	{
		free_map(d->map);
		free_str(d->north);
		free_str(d->south);
		free_str(d->west);
		free_str(d->east);
		free_str(d->floor);
		free_str(d->ceiling);
		free_str(d->buf);
		free_colors(d->colors, 3);
		free_colors(d->textures, 4);
		free_str(d->read_buf);
		get_next_line(-1);
		free_str((char *)d->line);
		free_mlx(d);
		free_player(d);
		free(d);
		d = NULL;
	}
	exit(0);
}

void	init_dblptr(char **dbptr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dbptr[i] = NULL;
		i++;
	}
}

void	init_data(t_data *d)
{
	d->line = NULL;
	d->map = NULL;
	d->north = NULL;
	d->south = NULL;
	d->west = NULL;
	d->east = NULL;
	d->floor = NULL;
	d->ceiling = NULL;
	init_dblptr(d->colors, 3);
	init_dblptr(d->textures, 4);
	d->buf = NULL;
	d->c = 0;
	d->f = 0;
	d->read_buf = NULL;
	d->width = 0;
	d->heigth = 0;
	d->window = NULL;
	d->mlx_ptr = NULL;
	d->addr = NULL;
	d->img = NULL;
	d->player = NULL;
	d->pi = acos(-1.0);
}

void	init_player(t_data *d)
{
	d->player->x = 0;
	d->player->y = 0;
	d->player->up = false;
	d->player->down = false;
	d->player->left = false;
	d->player->right = false;
	d->player->map_x = 0;
	d->player->map_y = 0;
	printf("player->x: %f\n", d->player->x);
	printf("player->y: %f\n", d->player->y);
}

void	*ft_calloc(t_data *d, size_t nmemb, size_t size)
{
	char	*buffer;
	size_t	i;

	i = -1;
	if (!nmemb || !size)
		return (error_clean(d), NULL);
	if (size > SIZE_MAX / nmemb)
		return (error_clean(d), NULL);
	buffer = (void *)malloc(size * nmemb);
	if (!buffer)
		return (ft_printe("Error, malloc fail\n"), error_clean(d), NULL);
	while (++i < size)
		buffer[i] = '\0';
	return (buffer);
}

int	ft_dataigit_count(int n)
{
	int	digits;

	if (n < 0)
	{
		digits = 1;
		n *= -1;
	}
	else
		digits = 0;
	if (n == 0)
		digits = 1;
	while (n > 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n, t_data *data)
{
	char		*result;
	int			digits;
	int			num;

	num = n;
	digits = ft_dataigit_count(num);
	if (n < 0)
		num *= -1;
	result = ft_calloc(data, sizeof(char), (digits + 1));
	while (digits--)
	{
		*(result + digits) = (num % 10) + 48;
		num = num / 10;
	}
	if (n < 0)
		*(result + 0) = '-';
	return (result);
}

long long	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!nptr || nptr[0] == '\0')
		return (0);
	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

char	*ft_strdup(t_data *d, const char *s)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[j] != '\0')
		j++;
	ptr = ft_calloc(d, sizeof(char), (j + 1));
	while (i < j)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s1[i] && s1[i] == s2[i])
		{
			while (s1[i] && s1[i] == s2[i] && i < n)
				i++;
		}
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

void	save_map(t_data *d, char *line)
{
	char	**buf;
	int		i;

	i = 0;
	if (!d->north || !d->south || !d->west || !d->east
		|| !d->floor || !d->ceiling)
		return ;
	if (!d->map)
	{
		d->map = ft_calloc(d, 2, sizeof(char *));
		d->map[0] = NULL;
	}
	while (d->map[i])
		i++;
	buf = ft_calloc(d, i + 2, sizeof(char *));
	i = -1;
	while (d->map[++i] != NULL)
		buf[i] = d->map[i];
	buf[i] = ft_strdup(d, line);
	buf[i + 1] = NULL;
	free(d->map);
	d->map = buf;
}

char	*ft_substr(t_data *data, char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;

	i = 0;
	if (!(s))
		return (0);
	sub = ft_calloc(data, sizeof(char), (len + 1));
	while (i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	return (sub);
}

void	cut_num(t_data *d, char *color, int i, int loop)
{
	int	l;

	l = 0;
	if (!color[i] || color[i] < 48 || color[i] > 57)
		return ;
	while (color[i + l] && color[i + l] >= 48 && color[i + l] <= 57)
		l++;
	if (loop == 3 || l == 0)
		return ;
	d->colors[loop] = ft_substr(d, color, i, l);
	d->buf = ft_itoa(ft_atoi(d->colors[loop]), d);
	if (ft_atoi(d->colors[loop]) != ft_atoi(d->buf)
		|| ft_atoi(d->colors[loop]) >= 256
		|| ft_atoi(d->colors[loop]) < 0)
		return (ft_printe("Error, wrong RGB number\n"), error_clean(d));
	free_str(d->buf);
	d->buf = NULL;	//important idk why
}

int	to_rgb(t_data *d)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(d->colors[0]) * 256 * 256;
	g = ft_atoi(d->colors[1]) * 256;
	b = ft_atoi(d->colors[2]);
	free_str(d->colors[0]);
	d->colors[0] = NULL;
	free_str(d->colors[1]);
	d->colors[1] = NULL;
	free_str(d->colors[2]);	// those are important idk why
	d->colors[2] = NULL;
	return (r + g + b);
}

void	check_rgb(t_data *data, char *color, int *to_store)
{
	int	i;
	int	stk;

	i = 1;
	stk = 0;
	while (color[i] && color[i] != '\n')
	{
		while (color[i] && (color[i] == ','|| color[i] == 32
			|| color[i] == '\t'))
			i++;
		cut_num(data, color, i, stk);
		while (color[i] && color[i] >= 48 && color[i] <= 57 && (color[i] != ','
			|| color[i] != 32 || color[i] != '\t'))
			i++;
		if (color[i] && (color[i] != ',' && color[i] != 32 && color[i] != '\t'
			&& color[i] != '\n'))
			return (ft_printe("Error, wrong color format\n"),
			error_clean(data));
		stk++;
	}
	stk--;
	if (stk != 3)
		return (ft_printe("Error, wrong color format\n"),
			error_clean(data));
	*to_store = to_rgb(data);
}

int	sort_dataata_u_2(t_data *d, char *line, int i)
{
	if (!ft_strncmp("C ", line + i, 2) || !ft_strncmp("C\t", line + i, 2))
	{
		if (d->ceiling)
			return (ft_printe("Error, multiple definition of 'F'\n"),
				error_clean(d), 1);
		d->ceiling = ft_strdup(d, d->read_buf);
		check_rgb(d, d->ceiling, &d->c);
		return (1);
	}
	if (!ft_strncmp("F ", line + i, 2) || !ft_strncmp("F\t", line + i, 2))
	{
		if (d->floor)
			return (ft_printe("Error, multiple definition of 'F'\n"),
				error_clean(d), 1);
		d->floor = ft_strdup(d, d->read_buf);
		check_rgb(d, d->floor, &d->f);
		return (1);
	}
	return (0);
}

int	sort_dataata_u(t_data *d, char *line, int i)
{
	if (!ft_strncmp("WE ", line + i, 2) || !ft_strncmp("WE\t", line + i, 3))
	{
		if (d->west)
			return (ft_printe("Error, multiple definition of 'WE'\n"),
				error_clean(d), 1);
		d->west = ft_strdup(d, d->read_buf);
		return (1);
	}
	if (!ft_strncmp("EA ", line + i, 3) || !ft_strncmp("EA\t", line + i, 3))
	{
		if (d->east)
			return (ft_printe("Error, multiple definition of 'EA'\n"),
				error_clean(d), 1);
		d->east = ft_strdup(d, d->read_buf);
		return (1);
	}
	return (0);
}

void	sort_dataata(t_data *d, char *line, int i)
{
	while (line[i] && ((line[i] >= 7 && line[i] <= 13) || line[i] == 32))
		i++;
	if (!line[i] && (!d->map || !d->north || !d->south || !d->west
		|| !d->east || !d->floor || !d->ceiling))
		return ;
	if (!ft_strncmp("NO ", line + i, 3) || !ft_strncmp("NO\t", line + i, 3))
	{
		if (d->north)
			return (ft_printe("Error, multiple definition of 'NO'\n"),
				error_clean(d));
		d->north = ft_strdup(d, d->read_buf);
		return ;
	}
	else if (!ft_strncmp("SO ", line + i, 3)
		|| !ft_strncmp("SO\t", line + i, 3))
	{
		if (d->south)
			return (ft_printe("Error, multiple definition of 'SO'\n"),
				error_clean(d));
		d->south = ft_strdup(d, d->read_buf);
		return ;
	}
	else if (!sort_dataata_u(d, line, i) && !sort_dataata_u_2(d, line, i))
		save_map(d, line);
}

void	init_line_struct(t_data *d)
{
	int	i;
	int	length;

	i = 0;
	while (d->map[i])
		i++;
	if (d->heigth < i)
		d->heigth = i;
	d->line = ft_calloc(d, sizeof(t_line), i);
	i = -1;
	while (d->map[++i])
	{
		length = 0;
		d->line[i].num = i;
		while (d->map[i][length])
			length++;
		d->line[i].length = length;
		if (d->width < length)
			d->width = length;
	}
}

void	reading_data(t_data *d, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_printe("Error, map can not be open\n"), error_clean(d));
	d->read_buf = get_next_line(fd);
	if (!d->read_buf)
		return (error_clean(d));
	while (d->read_buf)
	{
		sort_dataata(d, d->read_buf, 0);
		free_str(d->read_buf);
		d->read_buf = get_next_line(fd);
	}
	if (!d->north || !d->south || !d->west || !d->east
			|| !d->floor || !d->ceiling || !d->map || !d->map[0]
			|| !d->map[0][0])
		return (ft_printe("Error, poor declaration of the map\n"),
			error_clean(d));
	init_line_struct(d);
}


int	map_name(char *map_name)
{
	int	i;

	i = 0;
	while (map_name[i])
		i++;
	i -= 4;
	if (i <= 0)
		return (0);
	if (!ft_strncmp(map_name + i, ".cub", 4))
		return (1);
	return (0);
}

void	check_walls(t_data *d, int i, int j)
{
	while (d->map[++i])
	{
		while (d->map[i][++j])
		{
			if ((d->map[i][j] == '0' || d->map[i][j] == 'N'
				|| d->map[i][j] == 'S' || d->map[i][j] == 'E'
				|| d->map[i][j] == 'W')
				&& (i == 0 || j == 0
				|| (!d->map[i - 1] || d->line[i - 1].length <= j
				|| d->map[i - 1][j] == 32 || d->map[i - 1][j] == '\n')
				|| (!d->map[i + 1] || d->line[i + 1].length <= j
				|| d->map[i + 1][j] == 32 || d->map[i + 1][j] == '\n')
				|| (!d->map[i][j - 1] || d->map[i][j - 1] == 32)
				|| (!d->map[i][j + 1] || d->map[i][j + 1] == 32
				|| d->map[i][j + 1] == '\n')))
			return (ft_printe("Error, map must be surrounded by walls\n"),
					error_clean(d));
		}
		j = -1;
	}
}

void	check_map(t_data *d, int pos, int i, int j)
{
	while (d->map[++i])
	{
		while (d->map[i][++j])
		{
			if (!pos && (d->map[i][j] == 'N' || d->map[i][j] == 'S'
				|| d->map[i][j] == 'E' || d->map[i][j] == 'W'))
				pos = 1;
			else if (pos && (d->map[i][j] == 'N' || d->map[i][j] == 'S'
				|| d->map[i][j] == 'E' || d->map[i][j] == 'W'))
				return (ft_printe("Error, multiple spawnpoint\n"),
					error_clean(d));
			if (d->map[i][j] != 32 && d->map[i][j] != '\n'
				&& d->map[i][j] != '1' && d->map[i][j] != '0'
				&& d->map[i][j] != 'N' && d->map[i][j] != 'S'
				&& d->map[i][j] != 'E' && d->map[i][j] != 'W')
			return (ft_printe("Error, unexpected character\n"),
					error_clean(d));
		}
		j = -1;
	}
	if (d->heigth > 15 || d->width > 16)
		return (ft_printe("Error, map is too big\n"),
					error_clean(d));
	check_walls(d, -1, -1);
}

int	handle_click_x(t_data *d)
{
	write(1, "You quit the game\n", 18);
	return (exit_clean(d), 0);
}

int	x_on_map(t_data *d, float pixel)
{
	return ((pixel - d->player->map_x) / BLOCK);
}

int	y_on_map(t_data *d, float pixel)
{
	return ((pixel - d->player->map_y) / BLOCK);
}

void	put_pixel(t_data *d, int x, int y, int color)
{
	// int	index;
	if (x >= WIDTH || y >= HEIGHT || x <= 0 || y <= 0)
		return ;
	mlx_pixel_put(d->mlx_ptr, d->window, x, y, color);
	// index = y * d->size_line + x * d->bpp / 8;
	// (void)d;
	// (void)color;
	// d->addr[index] = color & 0xFF;
	// d->addr[index + 1] = (color >> 8) & 0xFF;
	// d->addr[index + 2] = (color >> 16) & 0xFF;

}

void	draw_square(t_data *d, int x, int y, int size, int color)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(d, x + i, y, color);
	i = -1;
	while (++i < size)
		put_pixel(d, x, y + i, color);
	i = -1;
	while (++i < size)
		put_pixel(d, x + i, y + size, color);
	i = -1;
	while (++i <= size)
		put_pixel(d, x + size, y + i, color);
	
}

void	move_player(t_data *d)
{

	if (d->player->up == true
		&& ((d->map[y_on_map(d, d->player->y - SPEED - SIZE)][x_on_map(d, d->player->x + SIZE)] != '1')
		&& (d->map[y_on_map(d, d->player->y - SPEED - SIZE)][x_on_map(d, d->player->x - SIZE)] != '1')))
		d->player->y -= SPEED; //this
	if (d->player->down == true
		&& d->map[y_on_map(d, d->player->y + SPEED + SIZE)][x_on_map(d, d->player->x - SIZE)] != '1'
		&& d->map[y_on_map(d, d->player->y + SPEED + SIZE)][x_on_map(d, d->player->x + SIZE)] != '1')
		d->player->y += SPEED;
	if (d->player->left == true && d->map[y_on_map(d, d->player->y + SIZE)][x_on_map(d, d->player->x - SPEED - SIZE)] != '1' && d->map[y_on_map(d, d->player->y - SIZE)][x_on_map(d, d->player->x - SPEED - SIZE)] != '1')
		d->player->x -= SPEED;
	if (d->player->right == true && d->map[y_on_map(d, d->player->y + SIZE)][x_on_map(d, d->player->x + SPEED + SIZE)] != '1' && d->map[y_on_map(d, d->player->y - SIZE)][x_on_map(d, d->player->x + SPEED + SIZE)] != '1')
		d->player->x += SPEED;


	// x * BLOCK + (BLOCK / 2)
	// printf("x: %f | y: %f\n", d->player->x, d->player->y);
	// printf("map[][]: %c\n", d->map[y_on_map(d, d->player->y)][x_on_map(d, d->player->x - 1)]);
	// printf("X: %d | Y: %d\n", x_on_map(d, d->player->x), y_on_map(d, d->player->y));
	// printf("MOVE: %f\n", (d->player->x - (BLOCK / 2)) / BLOCK);
}

int	draw_loop(t_data *d)
{

	if (d->player->up == true || d->player->down == true || d->player->left == true || d->player->right == true)
	{
		draw_square(d, d->player->x, d->player->y, SIZE, 0); // deleting porpouse
		printf("x: %f | y: %f\n", d->player->x, d->player->y);
		move_player(d);
		draw_square(d, d->player->x, d->player->y, SIZE, d->f);
	}


	// move_player(d);
	// draw_square(d, d->player->x, d->player->y, 10, d->c);
	// mlx_put_image_to_window(d->mlx_ptr, d->window, d->img, 0, 0);
	return (1);
}

int	key_press(int key, t_data *d)
{
	if (key == XK_Escape)
	{
		write(1, "You quit the game\n", 18);
		exit_clean(d);
	}
	if (key == W && d->player->y > 0)
		d->player->up = true;
	if (key == A && d->player->x > 0)
		d->player->left = true;
	if (key == S && d->player->y < HEIGHT)
		d->player->down = true;
	if (key == D && d->player->x < WIDTH)
		d->player->right = true;
	// draw_square(d, d->player->x, d->player->y, 5, 0); // deleting porpouse
	// move_player(d);
	// draw_square(d, d->player->x, d->player->y, 5, d->f);
	return (0);
}

int	key_release(int key, t_data *d)
{
	if (key == XK_Escape)
	{
		write(1, "You quit the game\n", 18);
		exit_clean(d);
	}
	if (key == W || d->player->y < 0)
		d->player->up = false;
	if (key == A || d->player->x < 0)
		d->player->left = false;
	if (key == S || d->player->y >= HEIGHT)
		d->player->down = false;
	if (key == D || d->player->x >= WIDTH)
		d->player->right = false;
	return (0);
}

void	find_player(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (d->map[i])
	{
		while (d->map[i][j])
		{
			if (d->map[i][j] == 'N' || d->map[i][j] == 'S'
				|| d->map[i][j] == 'E' || d->map[i][j] == 'W')
			{
				d->player->map_x = j;
				d->player->map_y = i;
				d->player->x = j * BLOCK + (BLOCK / 2);
				d->player->y = i * BLOCK + (BLOCK / 2);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	flood_fill_down(t_data *d, int x, int y)
{
	if (y < 0 || x < 0 || !d->map[y] || d->line[y].length < x || !d->map[y][x] || d->map[y][x] == 'n'
		|| d->map[y][x] == 's' || d->map[y][x] == 'e'
		|| d->map[y][x] == 'w' || d->map[y][x] == 'o'
		|| d->map[y][x] == '2' || d->map[y][x] == '\n' || d->map[y][x] == 32)
		return ;
	if (d->map[y][x] == '1')
	{
		draw_square(d, ((x * BLOCK) + d->player->map_x), ((y * BLOCK) + d->player->map_y), BLOCK, d->c);
		return ;
	}
	if (d->map[y][x] == 'N')
		d->map[y][x] = 'n';
	if (d->map[y][x] == 'S')
		d->map[y][x] = 's';
	if (d->map[y][x] == 'E')
		d->map[y][x] = 'e';
	if (d->map[y][x] == 'W')
		d->map[y][x] = 'w';
	if (d->map[y][x] == '0')
		d->map[y][x] = 'o';
	flood_fill_down(d, x + 1, y);
	flood_fill_down(d, x - 1, y);
	flood_fill_down(d, x, y + 1);
	flood_fill_down(d, x, y - 1);
}

void	map_set_back(t_data *d, int x, int y)
{
	if (y < 0 || x < 0 || !d->map[y] || !d->map[y][x] || (y > 0
		&& d->line[y - 1].length < x) || (d->map[y + 1]
		&& d->line[y + 1].length < x) || d->map[y][x] == 'N'
		|| d->map[y][x] == 'S' || d->map[y][x] == 'E'
		|| d->map[y][x] == 'W' || d->map[y][x] == '0'
		|| d->map[y][x] == '1' || d->map[y][x] == '\n' || d->map[y][x] == 32)
		return ;
	if (d->map[y][x] == 'n')
		d->map[y][x] = 'N';
	if (d->map[y][x] == 's')
		d->map[y][x] = 'S';
	if (d->map[y][x] == 'e')
		d->map[y][x] = 'E';
	if (d->map[y][x] == 'w')
		d->map[y][x] = 'W';
	if (d->map[y][x] == 'o')
		d->map[y][x] = '0';
	if (d->map[y][x] == '2')
		d->map[y][x] = '1';
	if (d->map[y][x] == '\t')
		d->map[y][x] = '\n';
	map_set_back(d, x + 1, y);
	map_set_back(d, x - 1, y);
	map_set_back(d, x, y + 1);
	map_set_back(d, x, y - 1);
}

void	draw_map(t_data *d)
{
	find_player(d);
	flood_fill_down(d, d->player->map_x, d->player->map_y);
	map_set_back(d, d->player->map_x, d->player->map_y);
	print_map(d);
}

void	displaying(t_data *d)
{
	d->mlx_ptr = mlx_init();
	if (!d->mlx_ptr)
		return (ft_printe("Error, mlx_init\n"), error_clean(d));
	d->window = mlx_new_window(d->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!d->window)
		return (ft_printe("Error, mlx_new_window\n"), error_clean(d));
	d->img = mlx_new_image(d->mlx_ptr, WIDTH, HEIGHT);
	if (!d->img)
		return (ft_printe("Error, mlx_new_image\n"), error_clean(d));
	// d->addr = mlx_get_data_addr(d->mlx_ptr, &d->bpp, &d->size_line, &d->endian);
	// if (!d->addr)
	// 	return (ft_printe("Error, mlx_get_data_addr\n"), error_clean(d));
	// mlx_put_image_to_window(d->mlx_ptr, d->window, d->img, 0, 0); //new


	find_player(d);
	draw_square(d, d->player->x, d->player->y, SIZE, d->f);
	draw_map(d);
	
	mlx_hook(d->window, 17, 0, handle_click_x, d);
	mlx_hook(d->window, 2, 1L << 0, key_press, d);
	mlx_hook(d->window, 3, 1L << 1, key_release, d);
	mlx_loop_hook(d->mlx_ptr, draw_loop, d);
	// draw_loop(d);
	
	

	// if (d->player->up == true || d->player->down == true || d->player->left == true || d->player->right == true)
	// {
	// 	draw_square(d, d->player->x, d->player->y, 5, 0); // deleting porpouse
	// 	move_player(d);
	// 	draw_square(d, d->player->x, d->player->y, 5, d->f);
	// }

	// printf("d->c: %d\n", d->c);
	// printf("d->f: %d\n", d->f);
	mlx_loop(d->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_data		*d;
	t_player	*p;
	
	p = NULL;
	if (argc != 2)
		return(ft_printe("Error, map as input needed\n"), 1);
	if (!map_name(argv[1]))
		return(ft_printe("Error, map must be '.cub' format\n"), 1);
	d = malloc(sizeof(t_data));
	if (!d)
		return (ft_printe("Error, malloc fail\n"), 1);
	init_data(d);
	p = malloc(sizeof(t_player));
	if (!p)
		return (ft_printe("Error, malloc fail\n"), error_clean(d), 1);
	d->player = p;
	init_player(d);
	reading_data(d, argv);
	// print_map(d);
	check_map(d, 0, -1, -1);
	printf("pi: %f\n", d->pi);

	displaying(d);

	return (exit_clean(d), 0);
}
