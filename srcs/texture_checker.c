#include "../includes/cub3d.h"

int	check_rgb_values(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if(rgb[i] < 0 || rgb[i] > 255)
			return (showerror(NULL, "Invalid RGB color"));
		i++;
	}
	return (0);
}

unsigned long	convert_rgb_to_hex(int *rgb_tab)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

int	check_textures_validity(t_cub3d *cubed, t_fileinfo *textures)
{
	if (!textures->north || !textures->south || !textures->west
		|| !textures->east)
		return (showerror(cubed, "Missing textures"));
	if (!textures->floor || !textures->ceiling)
		return (showerror(cubed, "Missing floor or ceiling"));
	if (check_file(textures->north, 0)
		|| check_file(textures->south, 0)
		|| check_file(textures->west, 0)
		|| check_file(textures->east, 0)
		|| check_rgb_values(textures->floor)
		|| check_rgb_values(textures->ceiling))
		return (1);
	textures->hex_floor = convert_rgb_to_hex(textures->floor);
	textures->hex_ceiling = convert_rgb_to_hex(textures->ceiling);
	return (0);
}