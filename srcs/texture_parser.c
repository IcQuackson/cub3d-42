#include "../includes/cub3d.h"

char	*get_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' '))
		j++;
	len = j;
	while (line[len] && (line[len] != ' '))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' '))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

int	get_textures(t_fileinfo *file, char *line, int j)
{
	if(ft_strncmp(line, "NO", 2) == 0 && !(file->north))
		file->north = get_path(line, j + 2);
	else if (ft_strncmp(line, "SO", 2) == 0 && !(file->south))
		file->south = get_path(line, j + 2);
	else if (ft_strncmp(line, "EA", 2) == 0 && !(file->east))
		file->east = get_path(line, j + 2);
	else if (ft_strncmp(line, "WE", 2) == 0 && !(file->west))
		file->west = get_path(line, j + 2);
	else
		return (2);
	return (0);
}

int	get_text_and_color(t_cub3d *cubed, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1]) && !ft_isdigit(map[i][j]))
		{
			if (get_textures(&cubed->fileinfo, map[i], j) == 2)
				return (1);
			return (3);
		}	
		else
		{
			if (get_colors(cubed, &cubed->fileinfo, map[i], j) == 2)
				return (1);
			return (3);
		}	
	}
	else if (ft_isdigit(map[i][j]))
	{
		if (create_map(cubed, map, i) == 1)
			return (1);
		return (0);
	}
	return (4);
}

int	get_file_data(t_cub3d *cubed, char **map)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			flag = get_text_and_color(cubed, map, i, j);
			if (flag == 3)
				break ;
			else if (flag == 1)
				return (1);
			else if (flag == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (0);
}

