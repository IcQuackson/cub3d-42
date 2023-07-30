#include "../includes/cub3d.h"

void	init_img(t_cub3d *cubed, t_image *image, char *path)
{
	image->pixel_bits = 0;
	image->size_line = 0;
	image->endian = 0;
	image->img = mlx_xpm_file_to_image(data->mlx, path, &data->texinfo.size, &data->texinfo.size);
	image->address = (int *)mlx_get_data_addr(image->img, &image->pixel_bits, &image->size_line, &image->endian);
}

int	*xpm_to_img(t_cub3d *cubed, char *path)
{
	t_image	image;
	int		x;
	int		y;
	int		*buffer;

	init_img(cubed, &image, path);
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
		return (0);
	cubed->textures[0] = xpm_to_img(cubed, cubed->fileinfo.north);
	cubed->textures[1] = xpm_to_img(cubed, cubed->fileinfo.south);
	cubed->textures[2] = xpm_to_img(cubed, cubed->fileinfo.east);
	cubed->textures[3] = xpm_to_img(cubed, cubed->fileinfo.west);
}

void	init_fileinfo(t_fileinfo *file)
{
	file->north = NULL;
	file->south = NULL;
	file->west = NULL;
	file->east = NULL;
	file->x = 0;
	file->y = 0;
	file->floor = 0;
	file->ceiling = 0;
	file->size = 64;
	file->step = 0.0;
	file->pos = 0.0;
	file->hex_floor = 0x0;
	file->hex_ceiling = 0x0;
}

int	init_mlx(t_cub3d cubed)
{
	cubed->mlx = mlx_init();
	if (!cubed->mlx)
		return (0);
	cubed->win = mlx_new_window(cubed->mlx, WIDTH, HEIGHT, "Cub3D by Sussy Bakas");
	if (!cubed->win)
		return (0);
	init_textures(cubed);
	return (1);
}