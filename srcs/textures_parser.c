
#include "../includes/cub3d.h"



void	free_char_doub_ptr(char **pointer)
{
	int	i;

	if (!pointer)
		return ;
	i = 0;
	while (pointer[i])
	{
		free(pointer[i]);
		i++;
	}
	free(pointer);
}


t_cub3d	*init_data(void)
{
	t_cub3d	*game_data;

	game_data = malloc(sizeof(t_cub3d));
	if (!game_data)
		return (NULL);
	/* game_data->map_data = malloc(sizeof(t_map));
	if (!game_data->map_data)
		return (NULL); */
	game_data->scene = malloc(sizeof(t_scene));
	if (!game_data->scene)
		return (NULL);
	game_data->scene->north_texture_path = NULL;
	game_data->scene->south_texture_path = NULL;
	game_data->scene->west_texture_path = NULL;
	game_data->scene->east_texture_path = NULL;
	game_data->scene->lines = NULL;
	game_data->scene->ceil_rgb[0] = -1;
	game_data->scene->ceil_rgb[1] = -1;
	game_data->scene->ceil_rgb[2] = -1;
	game_data->scene->floor_rgb[0] = -1;
	game_data->scene->floor_rgb[1] = -1;
	game_data->scene->floor_rgb[2] = -1;
	game_data->map = NULL;
	game_data->mlx_win = NULL;
	return (game_data);
}

void	free_resources(t_cub3d *game_data)
{
	if (game_data->mlx_win && game_data->mlx)
		mlx_destroy_window(game_data->mlx, game_data->mlx_win);
	free(game_data->scene->north_texture_path);
	free(game_data->scene->south_texture_path);
	free(game_data->scene->west_texture_path);
	free(game_data->scene->east_texture_path);
	//free_char_doub_ptr(game_data->scene->lines);
	//free_char_doub_ptr(game_data->map);
	//free(game_data->map_data);
	free(game_data->scene);
	free(game_data);
	exit(0);
}

char	**get_lines(t_cub3d *game_data, char *map_file)
{
	int		fd;
	char	*line;
	char	**lines;
	int		i;

	i = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	lines = malloc(sizeof(char *) * (game_data->scene->num_lines + 1));
	if (!lines)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		lines[i] = ft_strdup(line);
		ft_strchr(lines[i], '\n')[0] = '\0';
		free(line);
		line = get_next_line(fd);
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}


int	get_split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	textures_are_loaded(t_cub3d *game_data)
{
	t_scene	*scene;

	scene = game_data->scene;
	if (!scene->north_texture_path || !scene->south_texture_path
		|| !scene->west_texture_path || !scene->east_texture_path
		|| scene->ceil_rgb[0] == -1 || scene->ceil_rgb[1] == -1
		|| scene->ceil_rgb[2] == -1 || scene->floor_rgb[0] == -1
		|| scene->floor_rgb[1] == -1 || scene->floor_rgb[2] == -1)
		return (0);
	return (1);
}

int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	parse_rgb_aux(t_cub3d *game_data, char *rgb, char asset)
{
	char	**split_line;
	int		result;
	int		i;
	int		j = 0;

	while (rgb[j] == ' ' || rgb[j] == '\t')
		j++;
	split_line = ft_split(rgb + j, ',');
	if (!split_line || get_split_len(split_line) != 3)
	{
		free_char_doub_ptr(split_line);
		return ;
	}
	i = -1;
	while (split_line[++i])
	{
		if (!ft_isdigit_str(split_line[i]))
			break ;
		result = ft_atoi(split_line[i]);
		if (result >= 0 && result <= 255)
		{
			if (asset == 'F')
				game_data->scene->floor_rgb[i] = result;
			else
				game_data->scene->ceil_rgb[i] = result;
		}
	}
	free_char_doub_ptr(split_line);
}

int	parse_rgb(t_cub3d *game_data, char *line)
{
	char	**split_line;
	int		result;

	split_line = ft_split(line, ' ');
	if (!split_line || get_split_len(split_line) != 2)
	{
		free_char_doub_ptr(split_line);
		return (0);
	}
	result = 1;
	if (ft_strcmp(split_line[0], "F") == 0)
		parse_rgb_aux(game_data, split_line[1], 'F');
	else if (ft_strcmp(split_line[0], "C") == 0)
		parse_rgb_aux(game_data, split_line[1], 'C');
	else
		result = 0;
	free_char_doub_ptr(split_line);
	return (result);
}

int	get_scene_data(t_cub3d *game_data, char *map_file)
{
	int		i;
	t_scene	*scene;

	scene = game_data->scene;
	scene->num_lines = get_num_lines(map_file);
	if (scene->num_lines <= 0)
		return (0);
	scene->lines = get_lines(game_data, map_file);
	if (!scene->lines)
		return (0);
	i = 0;
	while (scene->lines[++i])
	{
		printf("%s\n", scene->lines[i]);
		if (scene->lines[i][0] == '\0')
			continue ;
		if (/* !(parse_textures(game_data, scene->lines[i]) || */ parse_rgb(game_data, scene->lines[i]))
			return (0);
		if (textures_are_loaded(game_data))
			break ;
	}
	if (!textures_are_loaded(game_data))
		return (0);
    for (i = 0; i < scene->num_lines; i++)
    {
        if (ft_isdigit(scene->lines[i][0]))
            break;
    }
	return (1);
}
