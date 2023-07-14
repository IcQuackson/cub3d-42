#include "../includes/cub3d.h"

int	file_exists(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("File not found");
		return (0);
	}
	close(fd);
	return (1);
}

int	is_file_type(int type, char *file_path)
{
	char	*filename;

	filename = ft_strrchr(file_path, '/');
	if (filename)
		filename++;
	else
		filename = file_path;
	if (ft_strlen(filename) < 5)
		return (0);
	if (type == CUB)
		return (ft_strcmp(ft_strchr(filename, '.'), ".cub") == 0);
	if (type == XPM)
		return (ft_strcmp(ft_strchr(filename, '.'), ".xpm") == 0);
	else
		return (0);
}

int	is_valid_file(t_cub3d *cubed, char *file)
{
	(void) cubed;
	if (!file_exists(file))
		return (0);
	if (!is_file_type(CUB, file))
		return (0);
	/* if (!parse_data(cubed, file))
		return (0); */
	return (1);
}
