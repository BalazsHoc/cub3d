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

void	printe(char *str)
{
	while (*str)
		write(2, str++, 1);
}

void	free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	clean_exit(t_data *data)
{
	if (data)
	{
		
		free(data);
	}
}

void	init_data(t_data *data)
{
	data->map = NULL;
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->floor = NULL;
}

// void	*ft_calloc(size_t nmemb, size_t size, t_data *data)
// {
// 	void	*buffer;

// 	if (!nmemb || !size)
// 		return (NULL);
// 	if (size > SIZE_MAX / nmemb)
// 		return (clean_exit(data), NULL);
// 	buffer = (void *)malloc(size * nmemb);
// 	if (!buffer)
// 		return (clean_exit(data), NULL);
// 	ft_bzero(buffer, size * nmemb);
// 	return (buffer);
// }

int	main(int argc, char **argv)
{
	// (void)argc;
	(void)argv;
	t_data	*data;

	if (argc != 2)
		return(printe("Map as input needed\n"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (printe("malloc fail\n"), 1);
	init_data(data);
	// reading_data(data);
	return (clean_exit(data), 0);
}
