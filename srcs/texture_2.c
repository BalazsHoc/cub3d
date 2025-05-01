/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:53:55 by bhocsak           #+#    #+#             */
/*   Updated: 2025/05/01 14:53:56 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	set_tex_x(t_data *d, int type)
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
