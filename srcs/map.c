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
	if (d->heigth > 16 || d->width > 22)
		return (ft_printe("Error\nmap is too big\n"),
			error_clean(d));
	check_walls(d, -1, -1);
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
