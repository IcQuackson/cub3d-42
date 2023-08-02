#include "../includes/cub3d.h"

int	is_folder(char *arg)
{
	int		fd;
	int	ret;

	ret = 0;
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = 1;
	}
	return (ret);
}

int	is_cub_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u' || arg[len - 1] != 'b' || arg[len - 4] != '.'))
		return (0);
	return (1);
}

int	is_xpm_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p' || arg[len - 1] != 'm' || arg[len - 4] != '.'))
		return (0);
	return (1);
}

int	check_file(char *arg, int type)
{
	int	fd;

	if (is_folder(arg))
		return (showerror(NULL, "File is a directory"));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (showerror(NULL, "File not found"));
	close(fd);
	if (type && !is_cub_file(arg))
		return (showerror(NULL, "File is not a .cub file"));
	if (!type && !is_xpm_file(arg))
		return (showerror(NULL, "File is not a .xpm file"));
	return (0);
}

int	parse_args(t_cub3d *cubed, char **av)
{
	if (check_file(av[1], 1) == 1)
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