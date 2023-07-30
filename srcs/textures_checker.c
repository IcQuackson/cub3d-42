#include "../includes/cub3d.h"

int	check_file(t_cub3d *cubed, t_fileinfo *file)
{
	if (!file->north || !file->south || !file->west || !file->east || !file->floor || !file->ceiling)
		return (0);
	if (!check_file(file->north, false) || !check_file(file->south, false) || !check_file(file->west, false) || !check_file(file->east, false))
		return (0);
	//check RGB missing
	return (1);
}