/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:49:31 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 17:26:07 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	copy_pixeldata(t_cub3d *cubed, int *buffer, t_image image)
{
	int	x;
	int	y;

	y = -1;
	while (++y < cubed->fileinfo.size)
	{
		x = -1;
		while (++x < cubed->fileinfo.size)
			buffer[y * cubed->fileinfo.size + x]
				= image.addr[y * cubed->fileinfo.size + x];
	}
}

/**
 * The function `xpm_to_image` converts an XPM file to an image
 * and returns the image data as an array
 * of integers.
 * 
 * @param cubed A pointer to a struct of type t_cub3d, which contains
 * information about the game
 * environment and settings.
 * @param path The `path` parameter is a string that represents the 
 * file path of the XPM image file
 * that you want to convert to an image.
 * 
 * @return a pointer to an integer array (`int *`).
 */
int	*xpm_to_image(t_cub3d *cubed, char *path)
{
	t_image	image;
	int		*buffer;

	image.pixel_bits = 0;
	image.size_line = 0;
	image.endian = 0;
	image.img = mlx_xpm_file_to_image(cubed->mlx, 
			path, &cubed->fileinfo.size, &cubed->fileinfo.size);
	if (!image.img)
		return (NULL);
	image.addr = (int *)mlx_get_data_addr(image.img, &image.pixel_bits,
			&image.size_line, &image.endian);
	buffer = ft_calloc(1, (sizeof(int *)
				* cubed->fileinfo.size * cubed->fileinfo.size));
	if (!buffer)
		return (0);
	copy_pixeldata(cubed, buffer, image);
	mlx_destroy_image(cubed->mlx, image.img);
	return (buffer);
}

void	init_textures(t_cub3d *cubed)
{
	cubed->textures = ft_calloc(4, sizeof(int *));
	if (!cubed->textures)
		return ;
	printf("north: %s\n", cubed->fileinfo.north);
	cubed->textures[0] = xpm_to_image(cubed, cubed->fileinfo.north);
	cubed->textures[1] = xpm_to_image(cubed, cubed->fileinfo.south);
	cubed->textures[2] = xpm_to_image(cubed, cubed->fileinfo.east);
	cubed->textures[3] = xpm_to_image(cubed, cubed->fileinfo.west);
	if (!cubed->textures[0] || !cubed->textures[1]
		|| !cubed->textures[2] || !cubed->textures[3])
		handle_closewindow(cubed);
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

/**
 * The function "no_digit" checks if a given string
 * contains any digits and returns 1 if it does not,
 * and 0 if it does.
 * 
 * @param str The parameter `str` is a pointer to a character array (string).
 * 
 * @return the value of the flag variable.
 */
int	no_digit(char *str)
{
	int		i;
	int		flag;

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
