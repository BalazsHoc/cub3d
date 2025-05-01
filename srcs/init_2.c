/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:52:14 by bhocsak           #+#    #+#             */
/*   Updated: 2025/05/01 14:52:16 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	init_line_struct(t_data *d)
{
	int	i;
	int	length;

	i = 0;
	while (d->map[i])
		i++;
	if (d->heigth < i)
		d->heigth = i;
	d->line = ft_calloc(d, sizeof(t_line), i);
	i = -1;
	while (d->map[++i])
	{
		length = 0;
		d->line[i].num = i;
		while (d->map[i][length])
			length++;
		d->line[i].length = length;
		if (d->width < length)
			d->width = length;
	}
}
