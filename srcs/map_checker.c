#include "../includes/cub3d.h"

void	change_space_into_wall(t_cub3d *cubed)
{
	int	i;
	int	j;

	i = 0;
	while (cubed->map[i])
	{
		j = 0;
		while (cubed->map[i][j] == ' ')
			j++;
		while (cubed->map[i][++j])
		{
			if (cubed->map[i][j] == ' ' && j != cubed->map[i][ft_strlen(cubed->map[i]) - 1])
				cubed->map[i][j] = '1';
		}
		i++;
	}
}

int	check_sides2(char **map_tab, int i, int j)
{
	if (!map_tab || !map_tab[i] || !map_tab[i][j])
		return (0);
	while (map_tab[i][j] == ' ')
		j++;
	while (map_tab[i][j])
	{
		if (map_tab[i][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

int	check_sides(t_map *map, char **map_tab)
{
	int	i;
	int	j;

	if (!check_sides2(map_tab, 0, 0))
		return (0);
	i = 1;
	while (i < (map->height - 1))
	{
		j = ft_strlen(map_tab[i]) - 1;
		if (map_tab[i][j] != '1')
			return (0);
		i++;
	}
	if (!check_sides2(map_tab, i, 0))
		return (0);
	return (1);
}

int	check_characters(t_cub3d *cubed, char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	cubed->map_data.player_orientation = '0';
	while (map_tab[i])
	{
		j = 0;
		while (map_tab[i][j])
		{
			while (map_tab == ' ')
				j++;
			if (!(ft_strchr("10NSEW", map_tab[i][j])))
				return (0);
			if (ft_strchr("NSEW", map_tab[i][j]) && cubed->map_data.player_orientation != '0')
			{
				printf("More than 1 player\n");
				return (0);
			}
			if (ft_strchr("NSEW", map_tab[i][j]) && cubed->map_data.player_orientation == '0')
				cubed->map_data.player_orientation = map_tab[i][j];
			j++;
		}
		i++;
	}
	return (1);
}

int	check_player_position(t_cub3d *cubed, char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	if (cubed->player.dir == '0')
		return (0);
	return (1);
}

int	check_map_validity(t_cub3d *cubed, char **map_tab)
{
	if (!cubed->map)
		return (showerror(cubed, "No map found"));
	if (!check_sides(&cubed->map_data, map_tab))
		return (showerror(cubed, "Map is not closed"));
	if (cubed->map_data.height < 3)
		return (showerror(cubed, "Map is too small"));
	if(!check_characters(cubed, map_tab))
		return (showerror(cubed, "Map contains invalid characters"));
	return (1);
}