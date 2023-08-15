/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:42:39 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 16:45:54 by joao-per         ###   ########.fr       */
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
	printf("%s", str);
	write(1, "\n", 1);
	freexit(cubed);
	return (0);
}
