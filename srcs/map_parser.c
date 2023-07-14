#include "../includes/cub3d.h"

char	*get_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	i = 0;
	while (line[j] && (line[j] == ' '))
		j++;
	len = j;
	while (line[len] && (line[len] != ' '))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
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

int	parse_textures(t_cub3d *cubed, char *line, int j)
{
	if (line[j + 2] && ft_isprint(line[j + 2]))
		return (0);
	if (line[j] == 'N' && line[j + 1] == 'O' && !(cubed->scene->north_texture_path))
		cubed->scene->north_texture_path = get_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(cubed->scene->south_texture_path))
		cubed->scene->south_texture_path = get_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(cubed->scene->west_texture_path))
		cubed->scene->west_texture_path = get_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(cubed->scene->east_texture_path))
		cubed->scene->east_texture_path = get_path(line, j + 2);
	else
		return (0);
	return (1);
}

int store_file_info(t_cub3d *cubed, char **map, int i, int j)
{
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1]) && !ft_isdigit(map[i][j]))
		{
			if (!parse_textures(cubed, map[i], j))
				return (0);
			return (2);
		}	
		/* else
		{
			if (!parse_rgb(cubed, &cubed->texinfo, map[i], j))
				return (0);
			return (2);
		}	 */
	}
	/* else if (ft_isdigit(map[i][j]))
	{
		if (create_map())
			return (0);
		return (1);
	} */
	return (3);
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
			flag = store_file_info(cubed, map, i, j);
			if (flag == 2)
				break ;
			else if (flag == 0)
				return (0);
			else if (flag == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (1);
}