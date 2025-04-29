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
	int	i;

	i = -1;
	while (++i < 4 && d->mlx_ptr)
	{
		if (d->textures[i].img)
			mlx_destroy_image(d->mlx_ptr, d->textures[i].img);
		d->textures[i].img = NULL;
	}
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

void	init_rays(t_data *d)
{
	d->mx = 0;
	d->my = 0;
	d->r_angle = 0;
	d->rx = 0;
	d->ry = 0;
	d->step_x = 0;
	d->step_y = 0;
	d->ray_dir_x = 0;
	d->ray_dir_y = 0;
	d->delta_dist_x = 0;
	d->delta_dist_y = 0;
	d->side_dist_x = 0;
	d->side_dist_y = 0;
	d->y_wall = 0;
	d->tex_x = 0;
	d->tex_y = 0;
}

void	init_texture(t_data *d)
{
	d->textures[0].img = NULL;
	d->textures[1].img = NULL;
	d->textures[2].img = NULL;
	d->textures[3].img = NULL;
	d->textures[0].addr = NULL;
	d->textures[1].addr = NULL;
	d->textures[2].addr = NULL;
	d->textures[3].addr = NULL;
}

void	init_data(t_data *d)
{
	d->line = NULL;
	init_texture(d);
	d->map = NULL;
	d->north = NULL;
	d->south = NULL;
	d->west = NULL;
	d->east = NULL;
	d->floor = NULL;
	d->ceiling = NULL;
	init_dblptr(d->colors, 3);
	init_dblptr((char **)d->textures, 4);
	d->buf = NULL;
	d->c = 0;
	d->f = 0;
	d->read_buf = NULL;
	d->width = 0;
	d->heigth = 0;
	init_rays(d);
	d->window = NULL;
	d->mlx_ptr = NULL;
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
	d->player->turn_l = false;
	d->player->turn_r = false;
	d->player->map_x = 0;
	d->player->map_y = 0;
	d->player->angle = 0;
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
		return (ft_printe("Error\nmalloc fail\n"), error_clean(d), NULL);
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
	char	*result;
	int		digits;
	int		num;

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
		return (ft_printe("Error\nwrong RGB number\n"), error_clean(d));
	while (color[i + l] && color[i + l] >= 48 && color[i + l] <= 57)
		l++;
	if (loop == 3 || l == 0)
		return ;
	d->colors[loop] = ft_substr(d, color, i, l);
	d->buf = ft_itoa(ft_atoi(d->colors[loop]), d);
	if (ft_atoi(d->colors[loop]) != ft_atoi(d->buf)
		|| ft_atoi(d->colors[loop]) >= 256
		|| ft_atoi(d->colors[loop]) < 0)
		return (ft_printe("Error\nwrong RGB number\n"), error_clean(d));
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

int	only_whitespace(char *color)
{
	int	i;

	i = 0;
	while (color[i] && color[i] != '\n' && is_white_space(color[i]))
		i++;
	if (!color[i] || (color[i] && color[i] == '\n'))
		return (1);
	return (0);
}

void	check_rgb(t_data *d, char *color, int *to_store)
{
	int	i;
	int	stk;

	i = 1;
	stk = 0;
	while (color[i] && (is_white_space(color[i])))
		i++;
	while (color[i] && color[i] != '\n' && stk != 3)
	{
		cut_num(d, color, i, stk);
		stk++;
		while (color[i] && color[i] != '\n' && color[i] >= 48 && color[i] <= 57)
			i++;
		if ((stk != 3 && color[i] && color[i] != ',') || (stk == 3 && color[i]
			&& !only_whitespace(color + i)))
			return (ft_printe("Error\nwrong RGB number\n"), error_clean(d));
		if (color[i] && color[i] == ',')
			i++;
	}
	if (!only_whitespace(color + i))
		return (ft_printe("Error\nwrong color format\n"),
			error_clean(d));
	*to_store = to_rgb(d);
}

int	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}

char	*ft_strtrim(t_data *d, char const *s1, char const *set)
{
	size_t	end;

	if (s1 == 0 || set == 0)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	end = ft_strlen(s1);
	while (end != 0 && ft_strchr(set, s1[end]))
		end--;
	return (ft_substr(d, s1, 0, end + 1));
}

int	is_white_space(char c)
{
	if (c && ((c >= 7 && c <= 13) || c == 32))
		return (1);
	return (0);
}

void	convert_texture(t_data *d, int type, char *texture, int i)
{
	if (!texture[3] || texture[3] == '\n')
		return (ft_printe("Error\nwrong texture format\n"), error_clean(d));
	while (is_white_space(texture[i]))
		i++;
	if (!texture[i] || ft_strncmp(texture + i, "./", 2))
		return (ft_printe("Error\nno texture included\n"), error_clean(d));
	d->buf = ft_strtrim(d, texture + i, "\n");
	d->textures[type].img = mlx_xpm_file_to_image(d->mlx_ptr, d->buf, &d->textures[type].width, &d->textures[type].height);
	if (!d->textures[type].img)
		return (ft_printe("Error\ntexture could not be loaded\n"),
			error_clean(d));
	if (d->textures[type].height != TEXTURE_SIZE || d->textures[type].width != TEXTURE_SIZE)
		return (ft_printe("Error\ntexturesize must be 1024x1024\n"),
			error_clean(d));
	free_str(d->buf);
	d->buf = NULL;
	d->textures[type].addr = mlx_get_data_addr(d->textures[type].img,
	&d->textures[type].bpp,
	&d->textures[type].line_length,
	&d->textures[type].edian);
	if (!d->textures[type].addr)
		return (ft_printe("Error\ntexture could not be loaded\n"),
			error_clean(d));
}

int	sort_data_u_2(t_data *d, char *line, int i)
{
	if (!ft_strncmp("C ", line + i, 2) || !ft_strncmp("C\t", line + i, 2))
	{
		if (d->ceiling)
			return (ft_printe("Error\nmultiple definition of 'F'\n"),
				error_clean(d), 1);
		d->ceiling = ft_strdup(d, d->read_buf);
		check_rgb(d, d->ceiling, &d->c);
		return (1);
	}
	if (!ft_strncmp("F ", line + i, 2) || !ft_strncmp("F\t", line + i, 2))
	{
		if (d->floor)
			return (ft_printe("Error\nmultiple definition of 'F'\n"),
				error_clean(d), 1);
		d->floor = ft_strdup(d, d->read_buf);
		check_rgb(d, d->floor, &d->f);
		return (1);
	}
	return (0);
}

int	sort_data_u(t_data *d, char *line, int i)
{
	if (!ft_strncmp("WE ", line + i, 2) || !ft_strncmp("WE\t", line + i, 3))
	{
		if (d->west)
			return (ft_printe("Error\nmultiple definition of 'WE'\n"),
				error_clean(d), 1);
		d->west = ft_strdup(d, d->read_buf);
		return (1);
	}
	if (!ft_strncmp("EA ", line + i, 3) || !ft_strncmp("EA\t", line + i, 3))
	{
		if (d->east)
			return (ft_printe("Error\nmultiple definition of 'EA'\n"),
				error_clean(d), 1);
		d->east = ft_strdup(d, d->read_buf);
		return (1);
	}
	return (0);
}

void	sort_data(t_data *d, char *line, int i)
{
	while (line[i] && ((line[i] >= 7 && line[i] <= 13) || line[i] == 32))
		i++;
	if (!line[i] && (!d->map || !d->north || !d->south || !d->west
		|| !d->east || !d->floor || !d->ceiling))
		return ;
	if (!ft_strncmp("NO ", line + i, 3) || !ft_strncmp("NO\t", line + i, 3))
	{
		if (d->north)
			return (ft_printe("Error\nmultiple definition of 'NO'\n"),
				error_clean(d));
		d->north = ft_strdup(d, d->read_buf);
		return ;
	}
	else if (!ft_strncmp("SO ", line + i, 3)
		|| !ft_strncmp("SO\t", line + i, 3))
	{
		if (d->south)
			return (ft_printe("Error\nmultiple definition of 'SO'\n"),
				error_clean(d));
		d->south = ft_strdup(d, d->read_buf);
		return ;
	}
	else if (!sort_data_u(d, line, i) && !sort_data_u_2(d, line, i))
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
		// printf("num: %d | length: %d\n", d->line[i].num, d->line[i].length);
	}
}

void	reading_data(t_data *d, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_printe("Error\nmap can not be open\n"), error_clean(d));
	d->read_buf = get_next_line(fd);
	if (!d->read_buf)
		return (error_clean(d));
	while (d->read_buf)
	{
		sort_data(d, d->read_buf, 0);
		free_str(d->read_buf);
		d->read_buf = get_next_line(fd);
	}
	if (!d->north || !d->south || !d->west || !d->east
			|| !d->floor || !d->ceiling || !d->map || !d->map[0]
			|| !d->map[0][0])
		return (ft_printe("Error\npoor declaration of the map\n"),
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

void	check_walls(t_data *d, int y, int x)
{
	while (d->map[++y])
	{
		while (d->map[y][++x])
		{
			if ((d->map[y][x] == '0' || d->map[y][x] == 'N'
				|| d->map[y][x] == 'S' || d->map[y][x] == 'E'
				|| d->map[y][x] == 'W')
				&& (y == 0 || x == 0
				|| (!d->map[y - 1] || d->line[y - 1].length <= x
				|| d->map[y - 1][x] == 32 || d->map[y - 1][x] == '\n')
				|| (!d->map[y + 1] || d->line[y + 1].length <= x
				|| d->map[y + 1][x] == 32 || d->map[y + 1][x] == '\n')
				|| (!d->map[y][x - 1] || d->map[y][x - 1] == 32)
				|| (!d->map[y][x + 1] || d->map[y][x + 1] == 32
				|| d->map[y][x + 1] == '\n')))
			return (ft_printe("Error\nmap must be surrounded by walls\n"),
					error_clean(d));
		}
		x = -1;
	}
}

void	check_map(t_data *d, int pos, int x, int y)
{
	while (d->map[++y])
	{
		while (d->map[y][++x])
		{
			if (!pos && (d->map[y][x] == 'N' || d->map[y][x] == 'S'
				|| d->map[y][x] == 'E' || d->map[y][x] == 'W'))
				pos = 1;
			else if (pos && (d->map[y][x] == 'N' || d->map[y][x] == 'S'
				|| d->map[y][x] == 'E' || d->map[y][x] == 'W'))
				return (ft_printe("Error\nmultiple spawnpoint\n"),
					error_clean(d));
			if (d->map[y][x] != 32 && d->map[y][x] != '\n'
				&& d->map[y][x] != '1' && d->map[y][x] != '0'
				&& d->map[y][x] != 'N' && d->map[y][x] != 'S'
				&& d->map[y][x] != 'E' && d->map[y][x] != 'W')
			return (ft_printe("Error\nunexpected character\n"),
					error_clean(d));
		}
		x = -1;
	}
	if (d->heigth > 16 || d->width > 22)
		return (ft_printe("Error\nmap is too big\n"),
					error_clean(d));
	check_walls(d, -1, -1);
}

int	handle_click_x(t_data *d)
{
	write(1, "You quit the game\n", 18);
	return (exit_clean(d), 0);
}

void	put_pixel(t_data *d, int x, int y, int color)
{
	if (x >= WIDTH || y >= HEIGHT || x <= 0 || y <= 0)
		return ;
	mlx_pixel_put(d->mlx_ptr, d->window, x, y, color);
}

void	draw_miniplayer(t_data *d, int pixel_x, int pixel_y, int size, int color)
{
	int	i;
	int	j;

	pixel_x -= size / 2;
	pixel_y -= size / 2;
	i = -1;
	j = -1;
	while (MINI_MAP && ++i < size)
	{
		while (++j < size)
			put_pixel(d, pixel_x + j, pixel_y + i, color);
		j = -1;
	}
}

void	draw_square(t_data *d, int pixel_x, int pixel_y, int size, int color)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < size)
	{
		while (++j < size)
			put_pixel(d, pixel_x + j, pixel_y + i, color);
		j = -1;
	}
}

int	is_wall(t_data *d, double new_x, double new_y)
{
	if (!d->map[(int)(new_y / WALL)][(int)(new_x / WALL)]
		|| d->map[(int)(new_y / WALL)][(int)(new_x / WALL)] == '1'
		|| d->map[(int)(new_y / WALL)][(int)(new_x / WALL)] == 32
		|| d->map[(int)(new_y / WALL)][(int)(new_x / WALL)] == '\n')
		return (1);
	return (0);
}

void	rotate_player(t_data *d, double *sin_a, double *cos_a)
{
	if (d->player->turn_l)
		d->player->angle -= R_SPEED;
	if (d->player->turn_r)
		d->player->angle += R_SPEED;
	if (d->player->angle < 0)
		d->player->angle = 2 * d->pi - R_SPEED;
	if (d->player->angle > 2 * d->pi)
		d->player->angle = 0 + R_SPEED;
	*sin_a = sin(d->player->angle);
	*cos_a = cos(d->player->angle);
}

void	move_player_coor(t_data *d)
{
	double	sin_a;
	double	cos_a;

	rotate_player(d, &sin_a, &cos_a);
	if (d->player->up && !is_wall(d, d->player->x + (cos_a * SPEED), d->player->y + (sin_a * SPEED)))
	{
		d->player->x += cos_a * SPEED;
		d->player->y += sin_a * SPEED;
	}
	if (d->player->down && !is_wall(d, d->player->x - (cos_a * SPEED), d->player->y - (sin_a * SPEED)))
	{
		d->player->x -= cos_a * SPEED;
		d->player->y -= sin_a * SPEED;
	}
	if (d->player->left && !is_wall(d, d->player->x + (sin_a * SPEED), d->player->y - (cos_a * SPEED)))
	{
		d->player->x += sin_a * SPEED;
		d->player->y -= cos_a * SPEED;
	}
	if (d->player->right && !is_wall(d, d->player->x - (sin_a * SPEED), d->player->y + (cos_a * SPEED)))
	{
		d->player->x -= sin_a * SPEED;
		d->player->y += cos_a * SPEED;
	}
}

void	draw_textures_u(int * line_height, int *draw_start, int *draw_end)
{
	*line_height *= WALL_RESIZE;
	*draw_start = -(*line_height) / 2 + HEIGHT / 2;
	if (*draw_start < -HEIGHT * WALL_RESIZE)
		*draw_start = -HEIGHT * WALL_RESIZE;
	*draw_end = (*line_height) / 2 + HEIGHT / 2;
	if (*draw_end > HEIGHT * WALL_RESIZE)
		*draw_end = HEIGHT * WALL_RESIZE;
}

void set_tex_x(t_data *d, int type)
{
	double	wall_hit;

	if (d->y_wall == 0)
		wall_hit = d->ry + ((d->side_dist_x - d->delta_dist_x) * d->ray_dir_y);
	else
		wall_hit = d->rx + ((d->side_dist_y - d->delta_dist_y) * d->ray_dir_x);
	wall_hit /= WALL;
	wall_hit -= (int)(wall_hit);
	d->tex_x = (int)(wall_hit * d->textures[type].width);
	if (d->tex_x < 0)
		d->tex_x = 0;
	if (d->tex_x >= d->textures[type].width)
		d->tex_x = d->textures[type].width - 1;
	if ((d->y_wall == 0 && d->ray_dir_x > 0)
		|| (d->y_wall == 1 && d->ray_dir_y < 0))
		d->tex_x = d->textures[type].width - d->tex_x - 1;
}

void	draw_textures(t_data *d, double distance, int cur_col_x, int type)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;

	y = 0;
	distance *= cos(d->r_angle - d->player->angle);
	line_height = ((int)(HEIGHT / distance));
	draw_textures_u(&line_height, &draw_start, &draw_end);
	set_tex_x(d, type);
	while (MINI_MAP && y < d->heigth * MINI_WALL && cur_col_x + MINI_WALL < d->width * MINI_WALL)
		y++;
	// y--;
	while (y++ < draw_start)
		mlx_pixel_put(d->mlx_ptr, d->window, cur_col_x, y, d->c);
	while (y++ < draw_end)
	{
		d->tex_y = (int)(y - draw_start) * d->textures[type].height / (draw_end - draw_start);
		if (d->tex_y >= TEXTURE_SIZE)
			d->tex_y = TEXTURE_SIZE - 1;
		else if (d->tex_y < 0)
			d->tex_y = 0;
		mlx_pixel_put(d->mlx_ptr, d->window, cur_col_x, y,
			*(unsigned int *)(d->textures[type].addr
			+ (unsigned int)((d->tex_y * d->textures[type].line_length)
			+ (unsigned int)(d->tex_x * (d->textures[type].bpp / 8)))));
	}
	while (y++ < HEIGHT)
		mlx_pixel_put(d->mlx_ptr, d->window, cur_col_x, y, d->f);
}

void	setup_xy(t_data *d)
{
	d->ray_dir_x = cos(d->r_angle);
	d->ray_dir_y = sin(d->r_angle);
	d->delta_dist_x = sqrt(1 + (d->ray_dir_y * d->ray_dir_y) / (d->ray_dir_x * d->ray_dir_x));
	d->delta_dist_y = sqrt(1 + (d->ray_dir_x * d->ray_dir_x) / (d->ray_dir_y * d->ray_dir_y));
	if (d->ray_dir_x < 0)
	{
		d->step_x = -1;
		d->side_dist_x = (d->rx - d->mx) * d->delta_dist_x;
	}
	else
	{
		d->step_x = 1;
		d->side_dist_x = (d->mx + 1 - d->rx) * d->delta_dist_x;
	}
	if (d->ray_dir_y < 0)
	{
		d->step_y = -1;
		d->side_dist_y = (d->ry - d->my) * d->delta_dist_y;
	}
	else
	{
		d->step_y = 1;
		d->side_dist_y = (d->my + 1.0 - d->ry) * d->delta_dist_y;
	}
}

void	raycast_u(t_data *d, int cur_col_x)
{
	d->rx = d->player->x;
	d->ry = d->player->y;
	d->mx = (int)d->rx;
	d->my = (int)d->ry;
	setup_xy(d);
	while (!is_wall(d, d->mx, d->my))
	{
		if (d->side_dist_x < d->side_dist_y)
		{
			d->side_dist_x += d->delta_dist_x;
			d->mx += d->step_x;
			d->y_wall = 0;
		}
		else
		{
			d->side_dist_y += d->delta_dist_y;
			d->my += d->step_y;
			d->y_wall = 1;
		}
	}
	if (d->y_wall == 1 && d->r_angle >= 0 && d->r_angle <= d->pi)
		draw_textures(d, d->side_dist_y - d->delta_dist_y, cur_col_x, SOUTH);
	else if (d->y_wall == 1)
		draw_textures(d, d->side_dist_y - d->delta_dist_y, cur_col_x, NORTH);
	else if (d->y_wall == 0 && d->r_angle > d->pi / 2 && d->r_angle < 3 * d->pi / 2)
		draw_textures(d, d->side_dist_x - d->delta_dist_x, cur_col_x, WEST);
	else
		draw_textures(d, d->side_dist_x - d->delta_dist_x, cur_col_x, EAST);
}

void	raycast(t_data *d)
{
	int	cur_col_x;

	cur_col_x = -1;
	d->r_angle = d->player->angle - ((FOV * (d->pi / 180)) / 2);
	if (d->r_angle < 0)
		d->r_angle += (2 * d->pi); 
	d->rx = d->player->x;
	d->ry = d->player->y;
	while (++cur_col_x < WIDTH)
	{
		raycast_u(d, cur_col_x);
		d->r_angle += (FOV * (d->pi / 180)) / WIDTH;
		if (d->r_angle >= 2 * d->pi)
			d->r_angle -= (2 * d->pi);
	}
}

int	drawing(t_data *d)
{
	if (d->player->up == true || d->player->down == true
		|| d->player->left == true || d->player->right == true
		|| d->player->turn_l == true || d->player->turn_r == true)
	{
		draw_miniplayer(d, (d->player->x / WALL) * MINI_WALL,
		(d->player->y / WALL) * MINI_WALL, MINI_PLAYER, 0); // deleting porpouse
		move_player_coor(d);
		draw_miniplayer(d, (d->player->x / WALL) * MINI_WALL,
		(d->player->y / WALL) * MINI_WALL, MINI_PLAYER, 0xFF00FF); // without its blinking
		draw_mini_map(d);
		draw_miniplayer(d, (d->player->x / WALL) * MINI_WALL,
		(d->player->y / WALL) * MINI_WALL, MINI_PLAYER, 0xFF00FF);
		raycast(d);
	}
	return (1);
}

int	key_press(int key, t_data *d)
{
	if (key == XK_Escape)
	{
		write(1, "You quit the game\n", 18);
		exit_clean(d);
	}
	if (key == W)
		d->player->up = true;
	if (key == A)
		d->player->left = true;
	if (key == S)
		d->player->down = true;
	if (key == D)
		d->player->right = true;
	if (key == LEFT)
		d->player->turn_l = true;
	if (key == RIGHT)
		d->player->turn_r = true;
	return (0);
}

int	key_release(int key, t_data *d)
{
	if (key == XK_Escape)
	{
		write(1, "You quit the game\n", 18);
		exit_clean(d);
	}
	if (key == W)
		d->player->up = false;
	if (key == A)
		d->player->left = false;
	if (key == S)
		d->player->down = false;
	if (key == D)
		d->player->right = false;
	if (key == LEFT)
		d->player->turn_l = false;
	if (key == RIGHT)
		d->player->turn_r = false;
	return (0);
}

void	set_angle(t_data *d, int x, int y)
{
	if (d->map[y][x] == 'N')
		d->player->angle = (3 * d->pi) / 2;
	if (d->map[y][x] == 'S')
		d->player->angle = d->pi / 2;
	if (d->map[y][x] == 'E')
		d->player->angle = 0;
	if (d->map[y][x] == 'W')
		d->player->angle = d->pi;
}

void	find_player(t_data *d)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (d->map[y])
	{
		while (d->map[y][x])
		{
			if (d->map[y][x] == 'N' || d->map[y][x] == 'S'
				|| d->map[y][x] == 'E' || d->map[y][x] == 'W')
			{
				set_angle(d, x, y);
				d->player->map_x = x;
				d->player->map_y = y;
				d->player->x = x * WALL + (WALL / 2);
				d->player->y = y * WALL + (WALL / 2);
				d->map[y][x] = '0';
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_mini_map(t_data *d)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (MINI_MAP && d->map[y])
	{
		while (d->map[y][x])
		{
			if (d->map[y][x] == '1')
				draw_square(d, x * MINI_WALL, y * MINI_WALL, MINI_WALL, 0x808080);
			x++;
		}
		x = 0;
		y++;
	}
}

void	displaying(t_data *d)
{
	find_player(d);
	d->mlx_ptr = mlx_init();
	if (!d->mlx_ptr)
		return (ft_printe("Error\nmlx_init\n"), error_clean(d));
	d->window = mlx_new_window(d->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!d->window)
		return (ft_printe("Error\nmlx_new_window\n"), error_clean(d));
	convert_texture(d, NORTH, d->north, 3);
	convert_texture(d, SOUTH, d->south, 3);
	convert_texture(d, WEST, d->west,3);
	convert_texture(d, EAST, d->east, 3);
	draw_miniplayer(d, (d->player->x / WALL) * MINI_WALL,
	(d->player->y / WALL) * MINI_WALL, MINI_PLAYER, 0xFF00FF);
	draw_mini_map(d);
	raycast(d);
	
	mlx_hook(d->window, 17, 0, handle_click_x, d);
	mlx_hook(d->window, 2, 1L << 0, key_press, d);
	mlx_hook(d->window, 3, 1L << 1, key_release, d);
	mlx_loop_hook(d->mlx_ptr, drawing, d);
	mlx_loop(d->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_data		*d;
	t_player	*p;
	
	p = NULL;
	if (argc != 2)
		return(ft_printe("Error\nmap as input needed\n"), 1);
	if (!map_name(argv[1]))
		return(ft_printe("Error\nmap must be '.cub' format\n"), 1);
	d = malloc(sizeof(t_data));
	if (!d)
		return (ft_printe("Error\nmalloc fail\n"), 1);
	init_data(d);
	p = malloc(sizeof(t_player));
	if (!p)
		return (ft_printe("Error\nmalloc fail\n"), error_clean(d), 1);
	d->player = p;
	init_player(d);
	reading_data(d, argv);
	// print_map(d);
	check_map(d, 0, -1, -1);
	// displaying(d);
	return (exit_clean(d), 0);
}
