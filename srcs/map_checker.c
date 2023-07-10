/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:46:41 by joao-per          #+#    #+#             */
/*   Updated: 2023/07/10 20:46:41 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == '\n');
}

int is_first_or_last_line_wall(char *line)
{
	int i = 0;

	while (line[i])
	{
		if (line[i] != '1')
		{
			free(line);
			return (0);
		}
		i++;
	}
	return (1);
}

int is_line_wall(char *line)
{
	if (line[0] != '1' || line[strlen(line) - 1] != '1')
	{
		printf("Error: Map is not closed\n");
		free(line);
		return (0);
	}
	return (1);
}

int is_map_closed(char *mapfile)
{
	int fd = open(mapfile, O_RDONLY);
	char *line;
	int first_line = 1;
	int last_line = 0;

	if (fd == -1)
	{
		perror("Error opening map file");
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (!(is_line_wall(line) || (first_line || last_line)) && !is_first_or_last_line_wall(line))
			return (0);
		first_line = 0;
		free(line);
		line = get_next_line(fd);
		if (!line)
			last_line = 1;
	}
	free(line);
	close(fd);
	return (1);
}

int read_map(char *mapfile)
{
	t_map map;

	get_x_and_y(&map, mapfile);
	store_map(&map, mapfile);
	if (!is_map_closed(mapfile))
	{
		printf("Map is not closed\n");
		return (0);
	}
	return (1);
}
