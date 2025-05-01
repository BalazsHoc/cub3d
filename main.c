/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:06:16 by bhocsak           #+#    #+#             */
/*   Updated: 2025/03/25 13:06:19 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_printe(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int	main(int argc, char **argv)
{
	t_data		*d;
	t_player	*p;

	p = NULL;
	if (argc != 2)
		return (ft_printe("Error\nmap as input needed\n"), 1);
	if (!map_name(argv[1]))
		return (ft_printe("Error\nmap must be '.cub' format\n"), 1);
	d = malloc(sizeof(t_data));
	if (!d)
		return (ft_printe("Error\nmalloc fail\n"), 1);
	init_data(d);
	p = malloc(sizeof(t_player));
	if (!p)
		return (ft_printe("Error\nmalloc fail\n"), error_clean(d), 1);
	d->player = p;
	init_player(d);
	reading_data(d, argv);
	if (MAP_SIZE && MAP_SIZE < 3)
		return (ft_printe("Error\nIf there is a limit of\
MAP_SIZE it must be bigger than 2\n"), error_clean(d), 1);
	check_map(d, 0, -1, -1);
	displaying(d);
	return (exit_clean(d), 0);
}
