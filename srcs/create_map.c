#include "../includes/cub3d.h"

int	count_map_lines(t_cub3d *cubed, char **file, int i)
{
	int	index_value;
	int	j;

	index_value = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ')
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	cubed->mapinfo.index_end_of_map = i;
	return (i - index_value);
}

int	fill_map(t_mapinfo *mapinfo, char **map_tab, int index)
{
	int		i;
	int		j;

	mapinfo->width = find_biggest_wall(mapinfo, index);
	i = -1;
	while (++i < mapinfo->height)
	{
		j = -1;
		map_tab[i] = malloc(sizeof(char) * (mapinfo->width + 1));
		if (!map_tab[i])
			return (0);
		while (mapinfo->file[index][++j] && mapinfo->file[index][j] != '\n')
			map_tab[i][j] = mapinfo->file[index][j];
		while (j < mapinfo->width)
			map_tab[i][j++] = '\0';
		index++;
	}
	map_tab[i] = NULL;
	return (0);
}

int	get_map_info(t_cub3d *cubed, char **file, int i)
{
	cubed->mapinfo.height = count_map_lines(cubed, file, i);
	cubed->map = malloc(sizeof(char *) * (cubed->mapinfo.height + 1));
	if (!cubed->map)
		return (0);
	if (fill_map(&cubed->mapinfo, cubed->map, i) == 1)
		return (1);
	return (0);
}

void	space_to_wall(t_cub3d *cubed)
{ 
	int	i;
	int	j;

	i = -1;
	while (cubed->map[++i])
	{
		j = 0;
		while (cubed->map[i][j] == ' ')
			j++;
		while (cubed->map[i][++j])
		{
			if (cubed->map[i][j] == ' ' && j != cubed->map[i][ft_strlen(cubed->map[i]) - 1])
				cubed->map[i][j] = '1';
		}
	}
}

int	create_map(t_cub3d *cubed, char **file, int i)
{
	if (get_map_info(cubed, file, i) == 1)
		return (1);
	space_to_wall(cubed);
	return (0);
}
