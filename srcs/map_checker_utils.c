/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:45:21 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 16:45:22 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_top_or_bottom(char **map_tab, int i, int j)
{
	if (!map_tab || !map_tab[i] || !map_tab[i][j])
		return (1);
	while (map_tab[i][j] == ' ')
		j++;
	while (map_tab[i][j])
	{
		if (map_tab[i][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	is_a_white_space(char c)
{
	if (c != ' ' && c != '\t' && c != '\n')
		return (1);
	else
		return (0);
}

int	check_end_of_map(t_mapinfo *map)
{
	int	i;
	int	j;

	i = map->index_end_of_map - 1;
	while (map->file[++i])
	{
		j = -1;
		while (map->file[i][++j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\n')
				return (0);
		}
	}
	return (1);
}

size_t	find_biggest_wall(t_mapinfo *map, int i)
{
	size_t	size;

	size = ft_strlen(map->file[i]);
	while (map->file[i])
	{
		if (ft_strlen(map->file[i]) > size)
			size = ft_strlen(map->file[i]);
		i++;
	}
	return (size);
}
