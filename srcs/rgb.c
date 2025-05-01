/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:53:06 by bhocsak           #+#    #+#             */
/*   Updated: 2025/05/01 14:53:07 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	cut_num(t_data *d, char *color, int i, int loop)
{
	int	l;

	l = 0;
	if (!color[i] || color[i] < 48 || color[i] > 57)
		return (ft_printe("Error\nwrong RGB number\n"), error_clean(d));
	while (color[i + l] && color[i + l] >= 48 && color[i + l] <= 57)
		l++;
	if (loop == 3 || l == 0)
		return ;
	d->colors[loop] = ft_substr(d, color, i, l);
	d->buf = ft_itoa(ft_atoi(d->colors[loop]), d);
	if (ft_atoi(d->colors[loop]) != ft_atoi(d->buf)
		|| ft_atoi(d->colors[loop]) >= 256
		|| ft_atoi(d->colors[loop]) < 0)
		return (ft_printe("Error\nwrong RGB number\n"), error_clean(d));
	free_str(d->buf);
	d->buf = NULL;
}

int	to_rgb(t_data *d)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(d->colors[0]) * 256 * 256;
	g = ft_atoi(d->colors[1]) * 256;
	b = ft_atoi(d->colors[2]);
	free_str(d->colors[0]);
	d->colors[0] = NULL;
	free_str(d->colors[1]);
	d->colors[1] = NULL;
	free_str(d->colors[2]);
	d->colors[2] = NULL;
	return (r + g + b);
}

void	check_rgb(t_data *d, char *color, int *to_store)
{
	int	i;
	int	stk;

	i = 1;
	stk = 0;
	while (color[i] && (is_white_space(color[i])))
		i++;
	while (color[i] && color[i] != '\n' && stk != 3)
	{
		cut_num(d, color, i, stk);
		stk++;
		while (color[i] && color[i] != '\n' && color[i] >= 48 && color[i] <= 57)
			i++;
		if ((stk != 3 && color[i] && color[i] != ',') || (stk == 3 && color[i]
				&& !only_whitespace(color + i)))
			return (ft_printe("Error\nwrong RGB number\n"), error_clean(d));
		if (color[i] && color[i] == ',')
			i++;
	}
	if (stk != 3 || !only_whitespace(color + i))
		return (ft_printe("Error\nwrong color format\n"),
			error_clean(d));
	*to_store = to_rgb(d);
}
