#include "../includes/cub3d.h"

/**
 * The function counts the number of lines in a map by iterating through a file and checking for the
 * presence of '1' characters.
 * 
 * @param cubed A pointer to a struct of type t_cub3d.
 * @param file A pointer to a pointer to a character array. It represents the contents of a file, where
 * each element of the array represents a line of the file.
 * @param i The parameter `i` is the starting index from where the function should start counting the
 * map lines.
 * 
 * @return the number of lines in the map section of the file.
 */
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

/**
 * The function `fill_map` takes a `t_mapinfo` struct, a 2D array `map_tab`, and an index as
 * parameters, and fills `map_tab` with characters from `mapinfo->file` until a newline character is
 * encountered.
 * 
 * @param mapinfo A pointer to a struct of type t_mapinfo, which contains information about the map
 * (such as width, height, and file contents).
 * @param map_tab A double pointer to a character array, representing the map.
 * @param index The index parameter is used to keep track of the current line in the file that is being
 * processed. It is incremented after each line is processed.
 * 
 * @return 0.
 */
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

/**
 * The function "get_map_info" initializes the map height, allocates memory for the map, and fills the
 * map with data from a file.
 * 
 * @param cubed A pointer to a struct of type t_cub3d.
 * @param file The "file" parameter is a pointer to a pointer to a character array. It is used to pass
 * the contents of a file to the function.
 * @param i The parameter "i" in the function "get_map_info" is used as an index to iterate through the
 * "file" array. It is used to keep track of the current line being processed in the "file" array.
 * 
 * @return an integer value.
 */
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

/**
 * The function "space_to_wall" replaces all spaces in the map with the character '1', except for the
 * last space in each row.
 * 
 * @param cubed The parameter "cubed" is a pointer to a struct of type "t_cub3d".
 */
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

/**
 * The function create_map takes a pointer to a struct, a double pointer to a char array, and an
 * integer as parameters, and returns 1 if get_map_info returns 1, otherwise it returns 0 after calling
 * the space_to_wall function.
 * 
 * @param cubed A pointer to a struct of type t_cub3d, which contains information about the game's
 * settings and state.
 * @param file A pointer to a pointer to a character array, representing the contents of a file.
 * @param i The parameter "i" is an integer that represents the index of the current line being
 * processed in the "file" array.
 * 
 * @return an integer value. If the condition `get_map_info(cubed, file, i) == 1` is true, then the
 * function will return 1. Otherwise, it will return 0.
 */
int	create_map(t_cub3d *cubed, char **file, int i)
{
	if (get_map_info(cubed, file, i) == 1)
		return (1);
	space_to_wall(cubed);
	return (0);
}
