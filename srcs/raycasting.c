/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:52:58 by bhocsak           #+#    #+#             */
/*   Updated: 2025/05/01 14:52:59 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_correct_texture(t_data *d, int cur_col_x)
{
	if (d->y_wall == 1 && d->r_angle >= 0 && d->r_angle <= d->pi)
		draw_textures(d, d->side_dist_y - d->delta_dist_y, cur_col_x, SOUTH);
	else if (d->y_wall == 1)
		draw_textures(d, d->side_dist_y - d->delta_dist_y, cur_col_x, NORTH);
	else if (d->y_wall == 0 && d->r_angle > d->pi / 2
		&& d->r_angle < 3 * d->pi / 2)
		draw_textures(d, d->side_dist_x - d->delta_dist_x, cur_col_x, WEST);
	else
		draw_textures(d, d->side_dist_x - d->delta_dist_x, cur_col_x, EAST);
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
	draw_correct_texture(d, cur_col_x);
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
