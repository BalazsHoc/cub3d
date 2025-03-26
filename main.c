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

void	free_map(char **map)
{
	int	i;

	i = -1;
	if (map != NULL)
	{
		while (map[++i])
			free_str(map[i]); 
	}
}

void	free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	error_clean(t_d *data)
{
	if (data)
	{
		free_map(data->map);
		free_str(data->north);
		free_str(data->south);
		free_str(data->west);
		free_str(data->east);
		free_str(data->floor);
		free_str(data->read_buf);
		free(data);
	}
	exit(1);
}

void	exit_clean(t_d *data)
{
	if (data)
	{
		free_map(data->map);
		free_str(data->north);
		free_str(data->south);
		free_str(data->west);
		free_str(data->east);
		free_str(data->floor);
		free_str(data->read_buf);
		free(data);
	}
	exit(0);
}

void	init_data(t_d *data)
{
	data->map = NULL;
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->floor = NULL;
	data->read_buf = NULL;
}

void	*ft_calloc(t_d *data, size_t nmemb, size_t size)
{
	char	*buffer;
	size_t	i;

	i = -1;
	if (!nmemb || !size)
		return (error_clean(data), NULL);
	if (size > SIZE_MAX / nmemb)
		return (error_clean(data), NULL);
	buffer = (void *)malloc(size * nmemb);
	if (!buffer)
		return (error_clean(data), NULL);
	while (i < size)
		buffer[i] = '\0';
	return (buffer);
}

char	*ft_strdup(t_d *data, const char *s)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[j] != '\0')
		j++;
	ptr = ft_calloc(data, sizeof(char), (j + 1));
	while (i < j)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s1[i] && s1[i] == s2[i])
		{
			while (s1[i] && s1[i] == s2[i] && i < n)
				i++;
		}
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

void	sort_data_utils(t_d *data, char *line, int i)
{
	if (!ft_strncmp("WE ", line + i, 2))
	{
		if (data->west)
			return (ft_printe("Multiple definition of 'WE'\n"), error_clean(data));
		data->west = ft_strdup(data, data->read_buf);
	}
	if (!ft_strncmp("EA ", line + i, 2))
	{
		if (data->east)
			return (ft_printe("Multiple definition of 'EA'\n"), error_clean(data));
		data->east = ft_strdup(data, data->read_buf);
	}
	if (!ft_strncmp("F ", line + i, 1))
	{
		if (data->floor)
			return (ft_printe("Multiple definition of 'F'\n"), error_clean(data));
		data->floor = ft_strdup(data, data->read_buf);
	}
}

void	sort_data(t_d *data, char *line)
{
	int	i;

	i = 0;
	while (line[i] && ((line[i] >= 7 && line[i] <= 13) || line[i] == 32))
		i++;
	if (!line[i])
		return ;
	if (!ft_strncmp("NO ", line + i, 2))
	{
		if (data->north)
			return (ft_printe("Multiple definition of 'NO'\n"), error_clean(data));
		data->north = ft_strdup(data, data->read_buf);
	}
	if (!ft_strncmp("SO ", line + i, 2))
	{
		if (data->south)
			return (ft_printe("Multiple definition of 'SO'\n"), error_clean(data));
		data->south = ft_strdup(data, data->read_buf);
	}
	sort_data_utils(data, line, i);
}

void	reading_data(t_d *data, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_printe("Map can not be open\n"), error_clean(data));
	data->read_buf = get_next_line(fd);
	if (!data->read_buf)
		return (error_clean(data));
	while (data->read_buf)
	{
		// printf("%s\n", data->read_buf);
		sort_data(data, data->read_buf);
		free_str(data->read_buf);
		data->read_buf = get_next_line(fd);
	}
	if (!data->north || !data->south || !data->west || !data->east || !data->floor)
		return (ft_printe("poor declaration of the map\n"));
	
}


int	map_name(char *map_name)
{
	int	i;

	i = 0;
	while (map_name[i])
		i++;
	i -= 4;
	if (i <= 0)
		return (1);
	if (!ft_strncmp(map_name + i, ".cub", 4))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_d	*data;

	if (argc != 2)
		return(ft_printe("Map as input needed\n"), 1);
	if (!map_name(argv[1]))
		return(ft_printe("Map must be '.cub' format\n"), 1);
	data = malloc(sizeof(t_d));
	if (!data)
		return (ft_printe("malloc fail\n"), 1);
	init_data(data);
	reading_data(data, argv);
	return (exit_clean(data), 0);
}
