#include "../includes/cub3d.h"

int	check_textures_validity(t_cub3d *cubed, t_scene textures)
{
	if (!textures->north_texture_path || !textures->south_texture_path || !textures->west_texture_path
		|| !textures->east_texture_path)
		return (showerror(cubed, "Missing texture path"));
	if (!textures->floor || !textures->ceiling)
		return (showerror(cubed, "Missing floor or ceiling"));
	if (!is_valid_file(textures->north_texture_path, XPM) || !is_valid_file(textures->south_texture_path, XPM)
		|| is_valid_file(textures->west_texture_path, XPM) || is_valid_file(textures->east_texture_path, XPM))
		return (0);
	return (1);
}