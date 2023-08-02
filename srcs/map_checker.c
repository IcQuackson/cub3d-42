#include "../includes/cub3d.h"

static int	check_top_or_bottom(char **map_tab, int i, int j)
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

int	is_a_white_space(char c)
{
	if (c != ' ' && c != '\t' && c != '\r'
		&& c != '\n' && c != '\v' && c != '\f')
		return (1);
	else
		return (0);
}

size_t	find_biggest_len(t_mapinfo *map, int i)
{
	size_t	biggest_len;

	biggest_len = ft_strlen(map->file[i]);
	while (map->file[i])
	{
		if (ft_strlen(map->file[i]) > biggest_len)
			biggest_len = ft_strlen(map->file[i]);
		i++;
	}
	return (biggest_len);
}

int	check_map_elements(t_cub3d *cubed, char **map_tab)
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
	return (0);
}

int	check_position_is_valid(t_cub3d *cubed, char **map_tab)
{
	int	i;
	int	j;

	i = (int)cubed->player.pos_y;
	j = (int)cubed->player.pos_x;
	if (ft_strlen(map_tab[i - 1]) < (size_t)j
		|| ft_strlen(map_tab[i + 1]) < (size_t)j
		|| is_a_white_space(map_tab[i][j - 1]) == 0
		|| is_a_white_space(map_tab[i][j + 1]) == 0
		|| is_a_white_space(map_tab[i - 1][j]) == 0
		|| is_a_white_space(map_tab[i + 1][j]) == 0)
		return (1);
	return (0);
}

int	check_player_position(t_cub3d *cubed, char **map_tab)
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
	if (check_position_is_valid(cubed, map_tab) == 1)
		return (showerror(cubed, "Invalid player position"));
	return (0);
}

int	check_map_is_at_the_end(t_mapinfo *map)
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
				return (1);
		}
	}
	return (0);
}

int	check_map_validity(t_cub3d *cubed, char **map_tab)
{
	if (!cubed->map)
		return (showerror(cubed, "No map found"));
	if (check_map_sides(&cubed->mapinfo, map_tab))
		return (showerror(cubed, "No Walls found"));
	if (cubed->mapinfo.height < 3)
		return (showerror(cubed, "Map is too small"));
	if (check_map_elements(cubed, map_tab))
		return (1);
	if (check_player_position(cubed, map_tab))
		return (1);
	if (check_map_is_at_the_end(&cubed->mapinfo))
		return (showerror(cubed, "Map is not at the end"));
	return (0);
}
