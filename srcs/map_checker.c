/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:42:49 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 16:42:49 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_map_sides(t_mapinfo *map, char **map_tab)
{
	int	i;
	int	j;

	if (check_top_or_bottom(map_tab, 0, 0) == 1)
		return (1);
	i = 1;
	while (i < (map->height - 1))
	{
		j = ft_strlen(map_tab[i]) - 1;
		if (map_tab[i][j] != '1')
			return (1);
		i++;
	}
	if (check_top_or_bottom(map_tab, i, 0) == 1)
		return (1);
	return (0);
}

int	check_chars(t_cub3d *cubed, char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	cubed->player.dir = '0';
	while (map_tab[i] != NULL)
	{
		j = 0;
		while (map_tab[i][j])
		{
			while (cubed->map[i][j] == ' ')
				j++;
			if (!(ft_strchr("10NSEW", map_tab[i][j])))
				return (showerror(cubed, "Invalid map element"));
			if (ft_strchr("NSEW", map_tab[i][j]) && cubed->player.dir != '0')
				return (showerror(cubed, "Invalid map element"));
			if (ft_strchr("NSEW", map_tab[i][j]) && cubed->player.dir == '0')
				cubed->player.dir = map_tab[i][j];
			j++;
		}
		i++;
	}
	return (1);
}

int	check_pos_is_valid(t_cub3d *cubed, char **map_tab)
{
	int	i;
	int	j;

	i = (int)cubed->player.pos_y;
	j = (int)cubed->player.pos_x;
	if (ft_strlen(map_tab[i - 1]) < (size_t)j
		|| ft_strlen(map_tab[i + 1]) < (size_t)j
		|| !is_a_white_space(map_tab[i][j - 1])
		|| !is_a_white_space(map_tab[i][j + 1])
		|| !is_a_white_space(map_tab[i - 1][j])
		|| !is_a_white_space(map_tab[i + 1][j]))
		return (1);
	return (0);
}

int	check_pos(t_cub3d *cubed, char **map_tab)
{
	int	i;
	int	j;

	if (cubed->player.dir == '0')
		return (showerror(cubed, "No player position found"));
	i = 0;
	while (map_tab[i])
	{
		j = 0;
		while (map_tab[i][j])
		{
			if (ft_strchr("NSEW", map_tab[i][j]))
			{
				cubed->player.pos_x = (double)j + 0.5;
				cubed->player.pos_y = (double)i + 0.5;
				map_tab[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (check_pos_is_valid(cubed, map_tab) == 1)
		return (showerror(cubed, "Invalid player position"));
	return (1);
}

int	check_map_validity(t_cub3d *cubed, char **map_tab)
{
	if (!cubed->map)
		return (showerror(cubed, "No map found"));
	if (check_map_sides(&cubed->mapinfo, map_tab))
		return (showerror(cubed, "No Walls found"));
	if (cubed->mapinfo.height < 3)
		return (showerror(cubed, "Map is too small"));
	if (!check_chars(cubed, map_tab))
		return (0);
	if (!check_pos(cubed, map_tab))
		return (0);
	if (!check_end_of_map(&cubed->mapinfo))
		return (showerror(cubed, "Map is not at the end"));
	return (1);
}
