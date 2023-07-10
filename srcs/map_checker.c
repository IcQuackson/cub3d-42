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
		if (line[0] != '1' || line[strlen(line) - 1] != '1')
		{
			printf("Error: Map is not closed\n");
			free(line);
			return (0);
		}
		if (first_line || last_line)
		{
			for (int i = 0; line[i]; i++)
			{
				if (line[i] != '1')
				{
					free(line);
					return (0);
				}
			}
		}
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

void get_x_and_y(t_map *map, char *filename)
{
    char *line;
    int fd;
    int oldx, x = 0;
    int y = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
	{
        perror("Error opening map file");
        exit(1);
    }

    line = get_next_line(fd);
    while (line)
	{
		printf("line: %s\n", line);
        oldx = x;
        x = ft_strlen(line);
        if (x != oldx && y > 0)
		{
            printf("Map is not rectangular\n");
            free(line);
            exit(1);
        }
        free(line);
        line = get_next_line(fd);
        y++;
    }
    free(line);
    close(fd);
    if (y == 0 || x == 0)
	{
        printf("Map is not correct or not well formatted\n");
        exit(1);
    }
    map->width = x;
    map->height = y;
}

void store_map(t_map *map, char *filename)
{
    char *line;
    int fd;
    int i, j;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
	{
        perror("Error opening map file");
        exit(1);
    }

    map->grid = malloc(sizeof(char *) * map->height);
    i = 0;
    while (i < map->height)
    {
        map->grid[i] = malloc(sizeof(char) * (map->width + 1));
        i++;
    }
    i = 0;
    line = get_next_line(fd);
    while (line)
	{
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
        free(line);
        line = get_next_line(fd);
        i++;
    }
    free(line);
    close(fd);
}


int read_map(char *mapfile)
{
    t_map map;

    get_x_and_y(&map, mapfile);
    store_map(&map, mapfile);
    if (!is_map_closed(mapfile))
	{
        printf("Map is not closed\n");
        return 0;
    }
    return 1;
}
