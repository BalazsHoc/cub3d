/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:51:30 by bhocsak           #+#    #+#             */
/*   Updated: 2025/05/01 14:51:32 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	handle_click_x(t_data *d)
{
	write(1, "You quit the game\n", 18);
	return (exit_clean(d), 0);
}

int	key_press(int key, t_data *d)
{
	if (key == XK_Escape)
	{
		write(1, "You quit the game\n", 18);
		exit_clean(d);
	}
	if (key == W)
		d->player->up = true;
	if (key == A)
		d->player->left = true;
	if (key == S)
		d->player->down = true;
	if (key == D)
		d->player->right = true;
	if (key == LEFT)
		d->player->turn_l = true;
	if (key == RIGHT)
		d->player->turn_r = true;
	return (0);
}

int	key_release(int key, t_data *d)
{
	if (key == XK_Escape)
	{
		write(1, "You quit the game\n", 18);
		exit_clean(d);
	}
	if (key == W)
		d->player->up = false;
	if (key == A)
		d->player->left = false;
	if (key == S)
		d->player->down = false;
	if (key == D)
		d->player->right = false;
	if (key == LEFT)
		d->player->turn_l = false;
	if (key == RIGHT)
		d->player->turn_r = false;
	return (0);
}
