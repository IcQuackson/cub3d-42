/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:44:04 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 15:44:05 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_rgb_values(int *rgb, t_cub3d *cubed)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (showerror(cubed, "Invalid RGB color"));
		i++;
	}
	return (1);
}

unsigned long	convert_rgb(int *rgb_tab)
{
	unsigned long	hex;

	hex = 0;
	hex |= rgb_tab[0] << 16;
	hex |= rgb_tab[1] << 8;
	hex |= rgb_tab[2];
	return (hex);
}

int	check_textures_validity(t_cub3d *cubed, t_fileinfo *textures)
{
	if (!textures->north || !textures->south || !textures->west
		|| !textures->east)
		return (showerror(cubed, "Missing textures"));
	if (!textures->floor || !textures->ceiling)
		return (showerror(cubed, "Missing floor or ceiling"));
	if (!check_file(textures->north, XPM, cubed) 
		|| !check_file(textures->south, XPM, cubed)
		|| !check_file(textures->west, XPM, cubed) 
		|| !check_file(textures->east, XPM, cubed)
		|| !check_rgb_values(textures->floor, cubed)
		|| !check_rgb_values(textures->ceiling, cubed))
		return (0);
	textures->hex_floor = convert_rgb(textures->floor);
	textures->hex_ceiling = convert_rgb(textures->ceiling);
	return (1);
}
