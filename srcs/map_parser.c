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

int	is_texture(char *line)
{
	if (!line)
		return (0);
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		return (1);
	return (0);
}

int	is_order_valid(char **lines)
{
	int	num_textures;
	int	num_rgb;
	int	i;

	num_textures = 4;
	num_rgb = 2;
	i = -1;
	while (lines[++i])
	{
		if (is_texture(lines[i]))
		{
			if (num_rgb != 0 && num_rgb != 2)
				return (0);
			num_textures--;
		}
		else if (!ft_strncmp(lines[i], "F", 1) || !ft_strncmp(lines[i], "C", 1))
		{
			if (num_textures != 0 && num_textures != 4)
				return (0);
			num_rgb--;
		}
	}
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
	if (!is_order_valid(scene->lines))
		return (0);
	while (i != -1 && scene->lines[i])
	{
		if (parse_textures(game_data, scene->lines[i]))
			(void) 0;
		else if (parse_rgb(game_data, scene->lines[i]))
			(void) 0;
		else
			break ;
		i++;
	}
	printf("n: %s\n", scene->north_texture_path);
	printf("s: %s\n", scene->south_texture_path);
	printf("w: %s\n", scene->west_texture_path);
	printf("e: %s\n", scene->east_texture_path);
	printf("c0: %d\n", scene->ceil_rgb[0]);
	printf("c1: %d\n", scene->ceil_rgb[1]);
	printf("c2: %d\n", scene->ceil_rgb[2]);
	printf("f0: %d\n", scene->floor_rgb[0]);
	printf("f1: %d\n", scene->floor_rgb[1]);
	printf("f2: %d\n", scene->floor_rgb[2]);
	if (!textures_are_loaded(game_data))
		return (0);
	return (store_map(game_data, scene->lines + i));
}
