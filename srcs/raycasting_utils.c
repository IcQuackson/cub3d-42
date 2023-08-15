/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:39:52 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 16:39:53 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_image_pixel(t_image *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

void	set_frame(t_cub3d *cubed, t_image *image, int x, int y)
{
	if (cubed->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, cubed->texture_pixels[y][x]);
	else if (y < HEIGHT / 2)
		set_image_pixel(image, x, y, cubed->fileinfo.hex_ceiling);
	else if (y < HEIGHT -1)
		set_image_pixel(image, x, y, cubed->fileinfo.hex_floor);
}
