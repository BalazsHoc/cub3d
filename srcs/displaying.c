/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displaying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:51:37 by bhocsak           #+#    #+#             */
/*   Updated: 2025/05/01 14:51:40 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	put_pixel(t_data *d, int x, int y, int color)
{
	char	*pixel;

	if (x >= WIDTH || y >= HEIGHT || x <= 0 || y <= 0)
		return ;
	pixel = d->screen_img[0].addr + (y * d->screen_img[0].line_length
			+ x * (d->screen_img[0].bpp / 8));
	*(unsigned int *)pixel = color;
}

void	screen_img(t_data *d)
{
	d->screen_img[0].img = mlx_new_image(d->mlx_ptr, WIDTH, HEIGHT);
	if (!d->screen_img[0].img)
		return (ft_printe("Error\nmlx_new_image() fail\n"),
			error_clean(d));
	d->screen_img[0].addr = mlx_get_data_addr(d->screen_img[0].img,
			&d->screen_img[0].bpp,
			&d->screen_img[0].line_length,
			&d->screen_img[0].edian);
	if (!d->screen_img[0].addr)
		return (ft_printe("Error\nmlx_get_data_addr() fail\n"),
			error_clean(d));
}

int	drawing(t_data *d)
{
	if (d->player->up == true || d->player->down == true
		|| d->player->left == true || d->player->right == true
		|| d->player->turn_l == true || d->player->turn_r == true)
	{
		move_player_coor(d);
		raycast(d);
		delete_mini_map(d);
		draw_mini_map(d);
		draw_miniplayer(d, (d->player->x / WALL) * MINI_WALL,
			(d->player->y / WALL) * MINI_WALL, MINI_PLAYER);
		mlx_put_image_to_window(d->mlx_ptr, d->window,
			d->screen_img[0].img, 0, 0);
	}
	return (1);
}

void	displaying(t_data *d)
{
	find_player(d);
	d->mlx_ptr = mlx_init();
	if (!d->mlx_ptr)
		return (ft_printe("Error\nmlx_init\n"), error_clean(d));
	convert_texture(d, NORTH, d->north, 3);
	convert_texture(d, SOUTH, d->south, 3);
	convert_texture(d, WEST, d->west, 3);
	convert_texture(d, EAST, d->east, 3);
	d->window = mlx_new_window(d->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!d->window)
		return (ft_printe("Error\nmlx_new_window\n"), error_clean(d));
	screen_img(d);
	raycast(d);
	delete_mini_map(d);
	draw_mini_map(d);
	draw_miniplayer(d, (d->player->x / WALL) * MINI_WALL,
		(d->player->y / WALL) * MINI_WALL, MINI_PLAYER);
	mlx_put_image_to_window(d->mlx_ptr, d->window, d->screen_img[0].img, 0, 0);
	mlx_hook(d->window, 17, 0, handle_click_x, d);
	mlx_hook(d->window, 2, 1L << 0, key_press, d);
	mlx_hook(d->window, 3, 1L << 1, key_release, d);
	mlx_loop_hook(d->mlx_ptr, drawing, d);
	mlx_loop(d->mlx_ptr);
}
