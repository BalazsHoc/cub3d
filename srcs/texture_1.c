/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:53:48 by bhocsak           #+#    #+#             */
/*   Updated: 2025/05/01 14:53:50 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	convert_texture(t_data *d, int type, char *texture, int i)
{
	if (!texture[3] || texture[3] == '\n')
		return (ft_printe("Error\nwrong texture format\n"), error_clean(d));
	while (is_white_space(texture[i]))
		i++;
	if (!texture[i] || ft_strncmp(texture + i, "./", 2))
		return (ft_printe("Error\nno texture included\n"), error_clean(d));
	d->buf = ft_strtrim(d, texture + i, "\n \t");
	d->textures[type].img = mlx_xpm_file_to_image(d->mlx_ptr, d->buf,
			&d->textures[type].width, &d->textures[type].height);
	if (!d->textures[type].img)
		return (ft_printe("Error\ntexture could not be loaded\n"),
			error_clean(d));
	if (d->textures[type].height != TEXTURE_SIZE
		|| d->textures[type].width != TEXTURE_SIZE)
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

void	draw_textures_u(int *line_height, int *draw_start, int *draw_end)
{
	*line_height *= WALL_RESIZE;
	*draw_start = -(*line_height) / 2 + HEIGHT / 2;
	if (*draw_start < -HEIGHT * WALL_RESIZE)
		*draw_start = -HEIGHT * WALL_RESIZE;
	*draw_end = (*line_height) / 2 + HEIGHT / 2;
	if (*draw_end > HEIGHT * WALL_RESIZE)
		*draw_end = HEIGHT * WALL_RESIZE;
}

void	draw_textures_loop(t_data *d, int cur_col_x, int type)
{
	while (d->draw_y++ < d->draw_end)
	{
		d->tex_y = ((int)(d->draw_y - d->draw_start) * d->textures[type].height
				/ (d->draw_end - d->draw_start));
		if (d->tex_y >= TEXTURE_SIZE)
		{
			d->tex_y = TEXTURE_SIZE - 1;
			return ;
		}
		else if (d->tex_y < 0)
		{
			d->tex_y = 0;
			return ;
		}
		put_pixel(d, cur_col_x, d->draw_y,
			*(unsigned int *)(d->textures[type].addr
				+ (unsigned int)((d->tex_y * d->textures[type].line_length)
					+ (unsigned int)(d->tex_x * (d->textures[type].bpp / 8)))));
	}
}

void	draw_textures(t_data *d, double distance, int cur_col_x, int type)
{
	d->draw_y = 0;
	distance *= cos(d->r_angle - d->player->angle);
	d->line_height = ((int)(HEIGHT / distance));
	draw_textures_u(&d->line_height, &d->draw_start, &d->draw_end);
	set_tex_x(d, type);
	while (MINI_MAP && d->draw_y < d->heigth * MINI_WALL && cur_col_x
		+ MINI_WALL < d->width * MINI_WALL)
		d->draw_y++;
	if (d->draw_y)
		d->draw_y--;
	while (d->draw_y++ <= d->draw_start)
		put_pixel(d, cur_col_x, d->draw_y, d->c);
	d->draw_y--;
	draw_textures_loop(d, cur_col_x, type);
	d->draw_y--;
	while (d->draw_y++ <= HEIGHT)
		put_pixel(d, cur_col_x, d->draw_y, d->f);
}
