/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:42:39 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 16:20:03 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_fileinfo(t_fileinfo *fileinfo)
{
	if (fileinfo->ceiling)
		free(fileinfo->ceiling);
	if (fileinfo->floor)
		free(fileinfo->floor);
	if (fileinfo->north)
		free(fileinfo->north);
	if (fileinfo->south)
		free(fileinfo->south);
	if (fileinfo->west)
		free(fileinfo->west);
	if (fileinfo->east)
		free(fileinfo->east);
}

void	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_pixels(t_cub3d *cubed)
{
	int	i;

	if (!cubed)
		return ;
	if (!cubed->texture_pixels)
		return ;
	i = 0;
	while (i < HEIGHT + 1)
	{
		if (cubed->texture_pixels[i])
			free(cubed->texture_pixels[i]);
		i++;
	}
	free(cubed->texture_pixels);
}

void	free_textures(t_cub3d *cubed)
{
	int	i;

	if (!cubed->textures)
		return ;
	i = 0;
	while (i < 4)
	{
		if (cubed->textures[i])
			free(cubed->textures[i]);
		i++;
	}
	free(cubed->textures);
}

void freexit(t_cub3d *cubed)
{
	if (!cubed)
		return ;
	free_textures(cubed);
	free_fileinfo(&cubed->fileinfo);
	if (cubed->mapinfo.file)
		free_double_ptr(cubed->mapinfo.file);
	if (cubed->map)
		free_double_ptr(cubed->map);
	free_pixels(cubed);
}

int	showerror(t_cub3d *cubed, char *str)
{
	(void) str;
	write(1, "\033[31mError\n\033[0;37m", 18);
	printf("%s", str);
	write(1, "\n", 1);
	freexit(cubed);
	return (0);
}
