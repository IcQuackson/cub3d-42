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
# define MAX_LINE_LENGTH 1000

int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == '\n');
}

int is_map_closed(char *map)
{
	size_t i;
	size_t j;

	i = 0;
	j = ft_strlen(map) - 1;
	while (map[i] != '\n')
	{
		if (map[i] != '1')
			return (0);
		i++;
	}
	while (map[j] != '\n')
	{
		if (map[j] != '1')
			return (0);
		j--;
	}
	i = 0;
	while (i < ft_strlen(map))
	{
		if (map[i] == '\n')
		{
			if (map[i - 1] != '1' || (i + 1 < ft_strlen(map) && map[i + 1] != '1'))
				return 0;
		}
		i++;
	}
	return (1);
}


int read_map(char *mapfile)
{
    int fd = open(mapfile, O_RDONLY);
    char buffer[MAX_LINE_LENGTH + 1];
    ssize_t bytes_read;
    int i;

	i = 0;
    if (fd == -1)
	{
        perror("Error opening map file");
        return (0);
    }
	while ((bytes_read = read(fd, buffer, MAX_LINE_LENGTH)) > 0)
	{
		buffer[bytes_read] = '\0';
		printf("bytes_read: %ld\n", bytes_read);
		while (i < bytes_read)
		{
			printf("buffer[%d]: %c\n", i, buffer[i]);
			if (!is_valid_char(buffer[i]))
			{
				printf("Invalid character in map: %c\n", buffer[i]);
				return (0);
			}
			i++;
		}
		printf("%s", buffer);
	}
    if (bytes_read == -1)
        perror("Error reading map file");
    if (!is_map_closed(buffer))
	{
        printf("Map is not closed\n");
        return (0);
    }
    close(fd);
	return (1);
}