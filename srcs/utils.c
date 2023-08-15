/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:42:39 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 17:23:14 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	freexit(t_cub3d *cubed)
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
	if (cubed->mlx && cubed->win)
	{
		mlx_destroy_window(cubed->mlx, cubed->win);
		mlx_destroy_display(cubed->mlx);
	}
	else if (cubed->mlx)
		mlx_destroy_display(cubed->mlx);
	if (cubed->mlx)
		free(cubed->mlx);
	freexit(cubed);
	return (0);
}
