/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:52:43 by bhocsak           #+#    #+#             */
/*   Updated: 2025/05/01 14:52:44 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	delete_mini_map(t_data *d)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (MINI_MAP && y < d->heigth * MINI_WALL)
	{
		while (x <= d->width * MINI_WALL)
		{
			if (d->map[y / MINI_WALL][x / MINI_WALL]
				&& d->map[y / MINI_WALL][x / MINI_WALL] != ' '
				&& d->map[y / MINI_WALL][x / MINI_WALL] != '\n'
				&& d->map[y / MINI_WALL][x / MINI_WALL] != '\t')
				put_pixel(d, x, y, 0);
			else if (!d->map[y / MINI_WALL][x / MINI_WALL])
				break ;
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_miniplayer(t_data *d, int pixel_x, int pixel_y, int size)
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
			put_pixel(d, pixel_x + j, pixel_y + i, MINI_PLAYER_C);
		j = -1;
	}
}

void	draw_square(t_data *d, int pixel_x, int pixel_y, int size)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < size)
	{
		while (++j < size)
			put_pixel(d, pixel_x + j, pixel_y + i, MINI_WALL_C);
		j = -1;
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
				draw_square(d, x * MINI_WALL, y * MINI_WALL, MINI_WALL);
			x++;
		}
		x = 0;
		y++;
	}
}
