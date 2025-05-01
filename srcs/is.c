/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:52:22 by bhocsak           #+#    #+#             */
/*   Updated: 2025/05/01 14:52:23 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	only_whitespace(char *color)
{
	int	i;

	i = 0;
	while (color[i] && color[i] != '\n' && is_white_space(color[i]))
		i++;
	if (!color[i] || (color[i] && color[i] == '\n'))
		return (1);
	return (0);
}

int	is_white_space(char c)
{
	if (c && ((c >= 7 && c <= 13) || c == 32))
		return (1);
	return (0);
}

int	is_wall(t_data *d, double new_x, double new_y)
{
	if (!d->map[(int)(new_y / WALL)][(int)(new_x / WALL)]
		|| d->map[(int)(new_y / WALL)][(int)(new_x / WALL)] == '1'
		|| d->map[(int)(new_y / WALL)][(int)(new_x / WALL)] == 32
		|| d->map[(int)(new_y / WALL)][(int)(new_x / WALL)] == '\n')
		return (1);
	return (0);
}
