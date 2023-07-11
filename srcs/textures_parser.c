
#include "../includes/cub3d.h"

void	free_char_doub_ptr(char **pointer)
{
	int	i;

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
	game_data->map_data = malloc(sizeof(t_map));
	if (!game_data->map_data)
		return (NULL);
	game_data->scene = malloc(sizeof(t_scene));
	if (!game_data->scene)
		return (NULL);
	game_data->scene->north_texture_path = NULL;
	game_data->scene->south_texture_path = NULL;
	game_data->scene->west_texture_path = NULL;
	game_data->scene->east_texture_path = NULL;
	game_data->scene->lines = NULL;
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
	free(game_data->map_data);
	free(game_data->scene);
	free(game_data);
	exit(0);
}

int	get_num_lines(char *map_file)
{
	int		fd;
	char	*line;
	int		num_lines;

	num_lines = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s\n", line);
		num_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (num_lines);
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
		|| !scene->west_texture_path || !scene->east_texture_path)
		return (0);
	return (1);
}

int	parse_textures(t_cub3d *game_data, char **lines)
{
	char	**split_line;
	int		i;

	i = -1;
	while (lines[++i])
	{
		if (lines[i][0] == '\0')
			continue ;
		split_line = ft_split(lines[i], ' ');
		if (!split_line || get_split_len(split_line) != 2)
			return (-1);
		if (ft_strcmp(split_line[0], "NO") == 0)
			game_data->scene->north_texture_path = ft_strdup(split_line[1]);
		else if (ft_strcmp(split_line[0], "SO") == 0)
			game_data->scene->south_texture_path = ft_strdup(split_line[1]);
		else if (ft_strcmp(split_line[0], "WE") == 0)
			game_data->scene->west_texture_path = ft_strdup(split_line[1]);
		else if (ft_strcmp(split_line[0], "EA") == 0)
			game_data->scene->east_texture_path = ft_strdup(split_line[1]);
		else if ((free(lines[i]), 1) && (free_char_doub_ptr(split_line), 1))
			return (-1);
		free(lines[i]);
		free_char_doub_ptr(split_line);
		if (textures_are_loaded(game_data))
			return (1);
	}
	return (i);
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
	i = parse_textures(game_data, scene->lines);
	if (i <= 0 || i == scene->num_lines)
		return (0);
	printf("%s\n", scene->north_texture_path);
	printf("%s\n", scene->south_texture_path);
	printf("%s\n", scene->west_texture_path);
	printf("%s\n", scene->east_texture_path);
	return (1);
}
