#include "../includes/cub3d.h"

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


int	check_textures_validity(t_scene *textures)
{
	if (!textures->north_texture_path || !textures->south_texture_path || !textures->west_texture_path
		|| !textures->east_texture_path)
		return (showerror(NULL, "Missing texture path"));
	if (!textures->ceil_rgb || !textures->floor_rgb)
		return (showerror(NULL, "Missing floor or ceiling"));
	if (!is_valid_file(textures->north_texture_path, XPM) || !is_valid_file(textures->south_texture_path, XPM)
		|| is_valid_file(textures->west_texture_path, XPM) || is_valid_file(textures->east_texture_path, XPM))
		return (0);
	return (1);
}