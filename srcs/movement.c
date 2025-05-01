/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:52:50 by bhocsak           #+#    #+#             */
/*   Updated: 2025/05/01 14:52:51 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

void	move_player_coor_u(t_data *d, double sin_a, double cos_a)
{
	if (d->player->left && !is_wall(d, d->player->x
			+ (sin_a * SPEED), d->player->y - (cos_a * SPEED)))
	{
		d->player->x += sin_a * SPEED;
		d->player->y -= cos_a * SPEED;
	}
	if (d->player->right && !is_wall(d, d->player->x
			- (sin_a * SPEED), d->player->y + (cos_a * SPEED)))
	{
		d->player->x -= sin_a * SPEED;
		d->player->y += cos_a * SPEED;
	}
}

void	move_player_coor(t_data *d)
{
	double	sin_a;
	double	cos_a;

	rotate_player(d, &sin_a, &cos_a);
	if (d->player->up && !is_wall(d, d->player->x
			+ (cos_a * SPEED), d->player->y + (sin_a * SPEED)))
	{
		d->player->x += cos_a * SPEED;
		d->player->y += sin_a * SPEED;
	}
	if (d->player->down && !is_wall(d, d->player->x
			- (cos_a * SPEED), d->player->y - (sin_a * SPEED)))
	{
		d->player->x -= cos_a * SPEED;
		d->player->y -= sin_a * SPEED;
	}
	move_player_coor_u(d, sin_a, cos_a);
}
