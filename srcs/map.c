/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:52:33 by bhocsak           #+#    #+#             */
/*   Updated: 2025/05/01 14:52:34 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	print_map(t_data *d)
{
	int	i;

	i = -1;
	while (d->map[++i])
		printf("%s", d->map[i]);
	printf("\n");
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
	if (!pos)
		return (ft_printe("Error\nNo spawnpoint\n"),
			error_clean(d));
	check_walls(d, -1, -1);
}

void	save_map(t_data *d, char *line)
{
	int		i;

	i = 0;
	if (!d->north || !d->south || !d->west || !d->east
		|| !d->floor || !d->ceiling)
		return ;
	if (!d->map)
		d->map = ft_calloc(d, sizeof(char *), 2);
	while (d->map[i])
		i++;
	d->buf_arr = ft_calloc(d, sizeof(char *), i + 2);
	i = -1;
	while (d->map[++i] != NULL)
		d->buf_arr[i] = d->map[i];
	d->buf_arr[i] = ft_strdup(d, line);
	d->buf_arr[i + 1] = NULL;
	free(d->map);
	d->map = d->buf_arr;
	d->buf_arr = NULL;
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
