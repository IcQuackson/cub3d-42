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
		if (!(is_line_closed(line) (last_line && !is_line_wall(line))))
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

int is_folder(char *mapfile)
{
	int i;

	i = 0;
	while (mapfile[i])
	{
		if (mapfile[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int is_cub(char *mapfile)
{
	int i;

	i = 0;
	while (mapfile[i])
	{
		if (mapfile[i] == '.')
		{
			if (mapfile[i + 1] == 'c' && mapfile[i + 2] == 'u'
				&& mapfile[i + 3] == 'b' && mapfile[i + 4] == '\0')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int is_xpm(char *mapfile)
{
	int i;

	i = 0;
	while (mapfile[i])
	{
		if (mapfile[i] == '.')
		{
			if (mapfile[i + 1] == 'x' && mapfile[i + 2] == 'p'
				&& mapfile[i + 3] == 'm' && mapfile[i + 4] == '\0')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int read_map(char *mapfile)
{
	t_map map;

	if (is_folder(mapfile))
	{
		printf("Error: Map file must be in a folder\n");
		return (0);
	}
	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening map file");
		return (0);
	}
	close(fd);
	if (!is_cub(mapfile) && !is_xpm(mapfile))
	{
		printf("Error: Map file must be .cub or .xpm\n");
		return (0);
	}
	return (1);
}
