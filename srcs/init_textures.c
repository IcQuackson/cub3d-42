#include "../includes/cub3d.h"

int	*xpm_to_image(t_cub3d *cubed, char *path)
{
	t_image	image;
	int		*buffer;
	int		x;
	int		y;

	image.pixel_bits = 0;
	image.size_line = 0;
	image.endian = 0;
	image.img = mlx_xpm_file_to_image(cubed->mlx, path, &cubed->fileinfo.size, &cubed->fileinfo.size);
	image.addr = (int *)mlx_get_data_addr(image.img, &image.pixel_bits, &image.size_line, &image.endian);
	buffer = ft_calloc(1, (sizeof(int *) * cubed->fileinfo.size * cubed->fileinfo.size));
	if (!buffer)
		return (0);
	y = -1;
	while (++y < cubed->fileinfo.size)
	{
		x = -1;
		while (++x < cubed->fileinfo.size)
			buffer[y * cubed->fileinfo.size + x] = image.addr[y * cubed->fileinfo.size + x];
	}
	mlx_destroy_image(cubed->mlx, image.img);
	return (buffer);
}

void	init_textures(t_cub3d *cubed)
{
	cubed->textures = ft_calloc(5, sizeof * cubed->textures);
	if (!cubed->textures)
		return ;
	printf("north: %s\n", cubed->fileinfo.north);
	cubed->textures[0] = xpm_to_image(cubed, cubed->fileinfo.north);
	cubed->textures[1] = xpm_to_image(cubed, cubed->fileinfo.south);
	cubed->textures[2] = xpm_to_image(cubed, cubed->fileinfo.east);
	cubed->textures[3] = xpm_to_image(cubed, cubed->fileinfo.west);
}

void	init_fileinfo(t_fileinfo *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->size = 64;
	textures->floor = 0;
	textures->ceiling = 0;
	textures->x = 0;
	textures->y = 0;
	textures->step = 0.0;
	textures->pos = 0.0;
	textures->hex_floor = 0x0;
	textures->hex_ceiling = 0x0;
}

int	no_digit(char *str)
{
	int		i;
	int	flag;

	i = 0;
	flag = 1;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			flag = 0;
		i++;
	}
	return (flag);
}

int	*copy_into_rgb_array(char **rgb_to_convert, int *rgb)
{
	int		i;

	i = -1;
	while (rgb_to_convert[++i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		if (rgb[i] == -1 || no_digit(rgb_to_convert[i]) == 1)
		{
			free_tab((void **)rgb_to_convert);
			free(rgb);
			return (0);
		}
	}
	free_tab((void **)rgb_to_convert);
	return (rgb);
}

int	*set_rgb(char *line)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		count;

	rgb_to_convert = ft_split(line, ',');
	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		free_tab((void **)rgb_to_convert);
		return (0);
	}
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return(0);
	return (copy_into_rgb_array(rgb_to_convert, rgb));
}

int	fill_color_textures(t_cub3d *cubed, t_fileinfo *textures, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]))
		return (showerror(cubed, "Error\nInvalid color\n"));
	if (!textures->ceiling && line[j] == 'C')
	{
		textures->ceiling = set_rgb(line + j + 1);
		if (textures->ceiling == 0)
			return (showerror(cubed, "Error\nInvalid color\n"));
	}
	else if (!textures->floor && line[j] == 'F')
	{
		textures->floor = set_rgb(line + j + 1);
		if (textures->floor == 0)
			return (showerror(cubed, "Error\nInvalid color\n"));
	}
	else
		return (showerror(cubed, "Error\nInvalid color\n"));
	return (0);
}