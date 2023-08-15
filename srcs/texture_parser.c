/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:42:08 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 15:42:27 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	fill_direction_textures(t_fileinfo *textures, char *line, int j)
{
	if (ft_strncmp(line, "NO", 2) == 0 && !(textures->north))
		textures->north = get_texture_path(line, j + 2);
	else if (ft_strncmp(line, "SO", 2) == 0 && !(textures->south))
		textures->south = get_texture_path(line, j + 2);
	else if (ft_strncmp(line, "WE", 2) == 0 && !(textures->west))
		textures->west = get_texture_path(line, j + 2);
	else if (ft_strncmp(line, "EA", 2) == 0 && !(textures->east))
		textures->east = get_texture_path(line, j + 2);
	else
		return (2);
	return (0);
}

int	fill_dir_and_text(t_cub3d *cubed, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] &&
			ft_isprint(map[i][j + 1]) && !ft_isdigit(map[i][j]))
		{
			if (fill_direction_textures(&cubed->fileinfo, map[i], j) == 2)
				return (1);
			return (3);
		}
		else
		{
			if (!fill_color_textures(cubed, &cubed->fileinfo, map[i], j))
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
			flag = fill_dir_and_text(cubed, map, i, j);
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
