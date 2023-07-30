#include "../includes/cub3d.h"

int is_folder(char *arg) 
{
	int	fd;

	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		return (1);
	}
	return (0);
}

int	file_exists(char *file_path)
{
	int	fd;

	if (is_folder(file_path))
		return (0);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("File not found");
		return (0);
	}
	close(fd);
	return (1);
}

int	is_cub_type(char *file_path)
{
	char	*filename;

	filename = ft_strrchr(file_path, '/');
	if (filename)
		filename++;
	else
		filename = file_path;
	if (ft_strlen(filename) < 5)
		return (0);
	return (ft_strcmp(ft_strchr(filename, '.'), ".cub") == 0);
}

int	is_xpm_type(char *file_path)
{
	char	*filename;

	filename = ft_strrchr(file_path, '/');
	if (filename)
		filename++;
	else
		filename = file_path;
	if (ft_strlen(filename) < 5)
		return (0);
	return (ft_strcmp(ft_strchr(filename, '.'), ".xpm") == 0);
}

int	is_valid_file(char *file, int type)
{
	if (is_dir(file))
		return (showerror(NULL, "File is a directory"));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (showerror(NULL, "File not found"));
	close(fd);
	if (!file_exists(file))
		return (showerror(NULL, "File does not exist"));
	if(type == CUB && !is_cub_type(CUB, file))
		return (showerror(NULL, "File is not a .cub file"));
	if(type == XPM && !is_xpm_type(XPM, file))
		return (showerror(NULL, "File is not a .xpm file"));
	return (1);
}

int check_args(t_cub3d *cubed, char **av)
{
	if (!is_valid_file(file, CUB))
		return (0);
	get_map_data(cubed, av[1]);
	if (get_file_cubed(cubed, cubed->mapinfo.file) == 1)
		return (1);
	return (1);
}
