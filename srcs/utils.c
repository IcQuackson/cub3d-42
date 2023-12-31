/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:42:39 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/18 10:34:21 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	freexit(t_cub3d *cubed)
{
	if (!cubed)
		return ;
	if (cubed->mlx && cubed->win)
	{
		mlx_destroy_window(cubed->mlx, cubed->win);
		mlx_destroy_display(cubed->mlx);
	}
	else if (cubed->mlx)
		mlx_destroy_display(cubed->mlx);
	if (cubed->mlx)
		free(cubed->mlx);
	free_textures(cubed);
	free_fileinfo(&cubed->fileinfo);
	if (cubed->mapinfo.file)
		free_double_ptr(cubed->mapinfo.file);
	if (cubed->map)
		free_double_ptr(cubed->map);
	free_pixels(cubed);
	exit(0);
}

int	showerror(t_cub3d *cubed, char *str)
{
	write(1, "\033[31mError\n\033[0;37m", 18);
	printf("%s\n", str);
	freexit(cubed);
	return (0);
}

void	start_program(void)
{
	printf("\033[32m\e[4m\e[1mWelcome to Cub3D!\n\033[0;37m");
	printf("\e[33;3m\e[1mCommands:\n\033[0;37m");
	printf("\033[32mW\033[0;37m - Move forward\n");
	printf("\033[32mA\033[0;37m - Move left\n");
	printf("\033[32mS\033[0;37m - Move backwards\n");
	printf("\033[32mD\033[0;37m - Move right\n");
	printf("\033[32m←\033[0;37m - Rotate left\n");
	printf("\033[32m→\033[0;37m - Rotate right\n");
}
