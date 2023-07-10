/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:50:56 by joao-per          #+#    #+#             */
/*   Updated: 2023/07/11 00:50:56 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void get_x_and_y(t_map *map, char *filename)
{
	char *line;
	int fd;
	int oldx;
	int x;
	int y;

	x = 0;
	y = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening map file");
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		oldx = x;
		x = ft_strlen(line);
		check_map_dimensions(x, oldx, y);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	free(line);
	close(fd);
	check_map_validity(x, y);
	map->width = x;
	map->height = y;
}

void fill_map_grid(t_map *map, char *line, int i)
{
	int j;

	j = 0;
	while (j < map->width)
	{
		map->grid[i][j] = line[j];
		if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E' || line[j] == 'W')
		{
			map->player_x = j;
			map->player_y = i;
			map->player_orientation = line[j];
		}
		j++;
	}
	map->grid[i][j] = '\0';
}

void store_map(t_map *map, char *filename)
{
	char *line;
	int fd;
	int i;

	i = -1;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening map file");
		exit(1);
	}
	map->grid = malloc(sizeof(char *) * map->height);
	while (++i < map->height)
		map->grid[i] = malloc(sizeof(char) * (map->width + 1));
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		fill_map_grid(map, line, i);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
}
