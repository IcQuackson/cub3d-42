#include "../includes/cub3d.h"

int	parse_textures(t_cub3d *cubed, char *line)
{
	char	**tokens;
	int		result;

	if (line && line[0] == '\0')
		return (1);
	result = 1;
	tokens = ft_split(line, ' ');
	if (!tokens || get_split_len(tokens) != 2)
		result = 0;
	else if (!ft_strncmp(line, "NO", 2) && !(cubed->scene->north_texture_path))
		cubed->scene->north_texture_path = ft_strdup(tokens[1]);
	else if (!ft_strncmp(line, "SO", 2) && !(cubed->scene->south_texture_path))
		cubed->scene->south_texture_path = ft_strdup(tokens[1]);
	else if (!ft_strncmp(line, "WE", 2) && !(cubed->scene->west_texture_path))
		cubed->scene->west_texture_path = ft_strdup(tokens[1]);
	else if (!ft_strncmp(line, "EA", 2) && !(cubed->scene->east_texture_path))
		cubed->scene->east_texture_path = ft_strdup(tokens[1]);
	else
		result = 0;
	free_char_doub_ptr(tokens);
	//printf("line: %s\n", line);
	//printf("result = %d\n", result);
	return (result);
}

// char **lines
// parse textures 1
//0 NO                                      dfedferdfsgsdfgsdfgsdfgsdfgsdfgdfsgsdf
//1 SO gdfgdfgfdg
//2 
//3 rgb 200, 200, 200 // parse rgb
//4 WE texture
//4 rgb 42, 234, -2  1
//5 // parse map -1
//6 mapa

// line = NO ./textures/north.xpm
// split(line) = [NO, ./textures/north.xpm] check if file exists && check if file type .xpm
// a\0

int	store_map(t_cub3d *game_data, char **lines)
{
	while (*lines)
	{
		if (ft_strcmp(*lines, ""))
			break ;
		lines++;
	}
	if (!*lines)
		return (0);
	game_data->map = lines;
	game_data->map_data.height = get_split_len(lines);
	return (1);
}

int	get_file_data(t_cub3d *game_data, char *map_file)
{
	int		i;
	t_scene	*scene;

	scene = game_data->scene;
	scene->num_lines = get_num_lines(map_file);
	scene->lines = get_lines(game_data, map_file);
	if (!scene->lines)
		return (0);
	i = 0;
	while (i != -1 && scene->lines[i])
	{
		if (!parse_textures(game_data, scene->lines[i]))
			break ;
		i++;
	}
	while (i != -1 && scene->lines[i])
	{
		if (!parse_rgb(game_data, scene->lines[i]))
			break ;
		i++;
	}
	if (!textures_are_loaded(game_data))
		return (0);
	printf("%s\n", scene->north_texture_path);
	printf("%s\n", scene->south_texture_path);
	printf("%s\n", scene->west_texture_path);
	printf("%s\n", scene->east_texture_path);
	printf("%d\n", scene->ceil_rgb[0]);
	printf("%d\n", scene->ceil_rgb[1]);
	printf("%d\n", scene->ceil_rgb[2]);
	printf("%d\n", scene->floor_rgb[0]);
	printf("%d\n", scene->floor_rgb[1]);
	printf("%d\n", scene->floor_rgb[2]);
	return (store_map(game_data, scene->lines + i));
}
