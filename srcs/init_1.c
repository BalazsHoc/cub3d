/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:52:09 by bhocsak           #+#    #+#             */
/*   Updated: 2025/05/01 14:52:11 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
