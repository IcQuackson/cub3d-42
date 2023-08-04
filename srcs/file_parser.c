#include "../includes/cub3d.h"

int	is_folder(char *filepath)
{
	int		fd;
	int	ret;

	ret = 0;
	fd = open(filepath, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = 1;
	}
	return (ret);
}

int	is_cub_type(char *filepath)
{
	size_t len;
	const char *file_extension;

	len = ft_strlen(filepath);
	file_extension = filepath + (len = ft_strlen(filepath)) - 4;
	if (len < 5 || ft_strcmp(file_extension, ".cub") != 0)
		return (0);
	return (1);
}

int	is_xpm_type(char *filepath)
{
	size_t len;
	const char *file_extension;

	len = ft_strlen(filepath);
	file_extension = filepath + (len = ft_strlen(filepath)) - 4;
	if (len < 5 || ft_strcmp(file_extension, ".xpm") != 0)
		return (0);
	return (1);
}


int	check_file(char *filepath, int type)
{
	int	fd;

	if (is_folder(filepath))
		return (showerror(NULL, "File is a directory"));
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (showerror(NULL, "File not found"));
	close(fd);
	if (type && !is_cub_type(filepath))
		return (showerror(NULL, "File is not a .cub file"));
	if (type == 0 && !is_xpm_type(filepath))
		return (showerror(NULL, "File is not a .xpm file"));
	return (0);
}

int	parse_args(t_cub3d *cubed, char **av)
{
	if (check_file(av[1], CUB))
		return (0);
	parse_data(av[1], cubed);
	if (get_file_data(cubed, cubed->mapinfo.file) == 1)
		return (0);
	if (check_map_validity(cubed, cubed->map) == 1)
		return (0);
	if (check_textures_validity(cubed, &cubed->fileinfo) == 1)
		return (0);
	init_direction(&cubed->player);
	return (1);
}