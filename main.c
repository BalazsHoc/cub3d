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

void	print_map(t_d *data)
{
	int	i;

	i = -1;
	while(data->map[++i])
		printf("%s", data->map[i]);
	printf("\n");
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

void	error_clean(t_d *data)
{
	if (data)
	{
		free_map(data->map);
		free_str(data->north);
		free_str(data->south);
		free_str(data->west);
		free_str(data->east);
		free_str(data->floor);
		free_str(data->ceiling);
		free_map(data->colors);
		free_str(data->read_buf);
		get_next_line(-1);
		free_str((char *)data->line);
		if (data->window)
			mlx_destroy_window(data->mlx_ptr, data->window);
		if (data->mlx_ptr)
			mlx_destroy_display(data->mlx_ptr);
		free_str(data->mlx_ptr);
		free(data);
	}
	exit(1);
}

void	exit_clean(t_d *data)
{
	if (data)
	{
		free_map(data->map);
		free_str(data->north);
		free_str(data->south);
		free_str(data->west);
		free_str(data->east);
		free_str(data->floor);
		free_str(data->ceiling);
		free_map(data->colors);
		free_str(data->read_buf);
		get_next_line(-1);
		free_str((char *)data->line);
		if (data->window)
			mlx_destroy_window(data->mlx_ptr, data->window);
		if (data->mlx_ptr)
			mlx_destroy_display(data->mlx_ptr);
		free_str(data->mlx_ptr);
		free(data);
		data = NULL;
	}
	exit(0);
}

void	init_data(t_d *data)
{
	data->line = NULL;
	data->map = NULL;
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->floor = NULL;
	data->ceiling = NULL;
	data->colors = NULL;
	data->read_buf = NULL;
	data->width = 0;
	data->heigth = 0;
	data->window = NULL;
	data->mlx_ptr = NULL;
}

void	*ft_calloc(t_d *data, size_t nmemb, size_t size)
{
	char	*buffer;
	size_t	i;

	i = -1;
	if (!nmemb || !size)
		return (error_clean(data), NULL);
	if (size > SIZE_MAX / nmemb)
		return (error_clean(data), NULL);
	buffer = (void *)malloc(size * nmemb);
	if (!buffer)
		return (ft_printe("Error, malloc fail\n"), error_clean(data), NULL);
	while (++i < size)
		buffer[i] = '\0';
	return (buffer);
}

size_t	ft_digit_count(long int n)
{
	size_t	digits;

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

char	*ft_itoa(long n, t_d *data)
{
	char		*result;
	size_t		digits;
	long long	num;

	num = n;
	digits = ft_digit_count(num);
	if (n < 0)
		num *= -1;
	result = ft_calloc(data, (digits + 1), sizeof(char));
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
	if (nptr[0] == '\0')
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

char	*ft_strdup(t_d *data, const char *s)
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
	ptr = ft_calloc(data, sizeof(char), (j + 1));
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

void	save_map(t_d *data, char *line)
{
	char	**buf;
	int		i;

	i = 0;
	if (!data->north || !data->south || !data->west || !data->east
		|| !data->floor || !data->ceiling)
		return ;
	if (!data->map)
	{
		data->map = ft_calloc(data, 2, sizeof(char *));
		data->map[0] = NULL;
	}
	while (data->map[i])
		i++;
	buf = ft_calloc(data, i + 2, sizeof(char *));
	i = -1;
	while (data->map[++i] != NULL)
		buf[i] = data->map[i];
	buf[i] = ft_strdup(data, line);
	buf[i + 1] = NULL;
	free(data->map);
	data->map = buf;
}

void	ft_strncpy(char *dest, char *src, int size)
{
	int	i;

	i = -1;
	if (!src || !*src)
		return ;
	while (++i < size)
		dest[i] = src[i];
}

void	split_num(t_d *data, char *color)
{
	int	i;
	int	loop;
	int	start;
	int	end;

	i = 0;
	loop = 3;
	start = 0;
	end = 0;
	data->colors = ft_calloc(data, sizeof(char *), 4);
	data->colors[loop] = NULL;
	while (loop--)
	{
		while (color[start] && (color[start] < 48 || color[start] > 57))
			start++;
		while (color[start + end] && color[start + end] >= 48 && color[start + end] <= 57)
			end++;
		printf("end %d + 1\n", end);
		data->colors[i] = ft_calloc(data, sizeof(char), end + 1);
		ft_strncpy(data->colors[i], color, end - start);
		start += end;
		end = 0;
		i++;
	}
}

void	check_rgb(t_d *data, char *color)
{
	int	i;
	int	stk;

	i = 0;
	stk = 0;
	while (color[i])
	{
		while (color[i] && (color[i] < 48 || color[i] > 57))
			i++;
		while (color[i] && color[i] >= 48 && color[i] <= 57)
			i++;
		stk++;
	}
	stk--;
	if (stk != 3)
		return (ft_printe("Error, wrong color format\n"),
			error_clean(data));
	split_num(data, color);
}

int	sort_data_u_2(t_d *data, char *line, int i)
{
	if (!ft_strncmp("C ", line + i, 2) || !ft_strncmp("C\t", line + i, 2))
	{
		if (data->ceiling)
			return (ft_printe("Error, multiple definition of 'F'\n"),
				error_clean(data), 1);
		data->ceiling = ft_strdup(data, data->read_buf);
		check_rgb(data, data->ceiling);
		return (1);
	}
	if (!ft_strncmp("F ", line + i, 2) || !ft_strncmp("F\t", line + i, 2))
	{
		if (data->floor)
			return (ft_printe("Error, multiple definition of 'F'\n"),
				error_clean(data), 1);
		data->floor = ft_strdup(data, data->read_buf);
		return (1);
	}
	return (0);
}

int	sort_data_u(t_d *data, char *line, int i)
{
	if (!ft_strncmp("WE ", line + i, 2) || !ft_strncmp("WE\t", line + i, 3))
	{
		if (data->west)
			return (ft_printe("Error, multiple definition of 'WE'\n"),
				error_clean(data), 1);
		data->west = ft_strdup(data, data->read_buf);
		return (1);
	}
	if (!ft_strncmp("EA ", line + i, 3) || !ft_strncmp("EA\t", line + i, 3))
	{
		if (data->east)
			return (ft_printe("Error, multiple definition of 'EA'\n"),
				error_clean(data), 1);
		data->east = ft_strdup(data, data->read_buf);
		return (1);
	}
	return (0);
}

void	sort_data(t_d *data, char *line, int i)
{
	while (line[i] && ((line[i] >= 7 && line[i] <= 13) || line[i] == 32))
		i++;
	if (!line[i] && (!data->map || !data->north || !data->south || !data->west
		|| !data->east || !data->floor || !data->ceiling))
		return ;
	if (!ft_strncmp("NO ", line + i, 3) || !ft_strncmp("NO\t", line + i, 3))
	{
		if (data->north)
			return (ft_printe("Error, multiple definition of 'NO'\n"),
				error_clean(data));
		data->north = ft_strdup(data, data->read_buf);
		return ;
	}
	else if (!ft_strncmp("SO ", line + i, 3) || !ft_strncmp("SO\t", line + i, 3))
	{
		if (data->south)
			return (ft_printe("Error, multiple definition of 'SO'\n"),
				error_clean(data));
		data->south = ft_strdup(data, data->read_buf);
		return ;
	}
	else if (!sort_data_u(data, line, i) && !sort_data_u_2(data, line, i))
		save_map(data, line);
}

void	init_line_struct(t_d *data)
{
	int	i;
	int	length;

	i = 0;
	while (data->map[i])
		i++;
	if (data->heigth < i)
		data->heigth = i;
	data->line = ft_calloc(data, sizeof(t_line), i);
	i = -1;
	while (data->map[++i])
	{
		length = 0;
		data->line[i].num = i;
		while (data->map[i][length])
			length++;
		data->line[i].length = length;
		if (data->width < length)
			data->width = length;
	}
}

void	reading_data(t_d *data, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_printe("Error, map can not be open\n"), error_clean(data));
	data->read_buf = get_next_line(fd);
	if (!data->read_buf)
		return (error_clean(data));
	while (data->read_buf)
	{
		// printf("%s\n", data->read_buf);
		sort_data(data, data->read_buf, 0);
		free_str(data->read_buf);
		data->read_buf = get_next_line(fd);
	}
	if (!data->north || !data->south || !data->west || !data->east
			|| !data->floor || !data->ceiling || !data->map || !data->map[0]
			|| !data->map[0][0])
		return (ft_printe("Error, poor declaration of the map\n"),
			error_clean(data));
	init_line_struct(data);
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

void	check_walls(t_d *data, int i, int j)
{
	while (data->map[++i])
	{
		// printf("\ni: %d\n", i);
		while (data->map[i][++j])
		{
			// printf("j: %d\n", j);
			if ((data->map[i][j] == '0' || data->map[i][j] == 'N'
				|| data->map[i][j] == 'S' || data->map[i][j] == 'E'
				|| data->map[i][j] == 'W')
				&& ((i == 0 || j == 0)
				|| (!data->map[i - 1] || data->line[i - 1].length < j
				|| data->map[i - 1][j] == 32 || data->map[i - 1][j] == '\n')
				|| (!data->map[i + 1] || data->line[i + 1].length <= j
				|| data->map[i + 1][j] == 32 || data->map[i + 1][j] == '\n')
				|| (!data->map[i][j - 1] || data->map[i][j - 1] == 32)
				|| (!data->map[i][j + 1] || data->map[i][j + 1] == 32
				|| data->map[i][j + 1] == '\n')))
			return (ft_printe("Error, map must be surrounded by walls\n"),
					error_clean(data));
		}
		j = -1;
	}
}

void	check_map(t_d *data, int pos, int i, int j)
{
	while (data->map[++i])
	{
		while (data->map[i][++j])
		{
			if (!pos && (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W'))
				pos = 1;
			else if (pos && (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W'))
				return (ft_printe("Error, multiple spawnpoint\n"),
					error_clean(data));
			if (data->map[i][j] != 32 && data->map[i][j] != '\n'
				&& data->map[i][j] != '1' && data->map[i][j] != '0'
				&& data->map[i][j] != 'N' && data->map[i][j] != 'S'
				&& data->map[i][j] != 'E' && data->map[i][j] != 'W')
			return (ft_printe("Error, unexpected character\n"),
					error_clean(data));
		}
		j = -1;
	}
	if (data->heigth > 15 || data->width > 15)
		return (ft_printe("Error, map is too big\n"),
					error_clean(data));
	check_walls(data, -1, -1);
}

int	handle_click_x(t_d *data)
{
	write(1, "You quit the game\n", 18);
	return (exit_clean(data), 0);
}

int	handle_keyboard(int key, t_d *data)
{
	if (key == XK_Escape)
	{
		write(1, "You quit the game\n", 18);
		exit_clean(data);
	}
	(void)data;
	// if (key == XK_w)
	// 	moving_w(data);
	// if (key == XK_a)
	// 	moving_a(data);
	// if (key == XK_s)
	// 	moving_s(data);
	// if (key == XK_d)
	// 	moving_d(data);
	return (0);
}

void	displaying(t_d *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		error_clean(data);
	data->window = mlx_new_window(data->mlx_ptr, 1600, 900, "cub3D");
	mlx_hook(data->window, 17, 0, handle_click_x, data);
	mlx_key_hook(data->window, handle_keyboard, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_d		*data;

	if (argc != 2)
		return(ft_printe("Error, map as input needed\n"), 1);
	if (!map_name(argv[1]))
		return(ft_printe("Error, map must be '.cub' format\n"), 1);
	data = malloc(sizeof(t_d));
	if (!data)
		return (ft_printe("Error, malloc fail\n"), 1);
	init_data(data);
	reading_data(data, argv);
	print_map(data);
	check_map(data, 0, -1, -1);
	displaying(data);
	return (exit_clean(data), 0);
}
