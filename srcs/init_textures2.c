/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:14:14 by pedgonca          #+#    #+#             */
/*   Updated: 2023/08/15 17:19:36 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	fill_color_textures(t_cub3d *cubed, t_fileinfo *textures, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]))
		return (showerror(cubed, "Invalid color"));
	if (!textures->ceiling && line[j] == 'C')
	{
		textures->ceiling = set_rgb(line + j + 1);
		if (textures->ceiling == 0)
			return (showerror(cubed, "Invalid color"));
	}
	else if (!textures->floor && line[j] == 'F')
	{
		textures->floor = set_rgb(line + j + 1);
		if (textures->floor == 0)
			return (showerror(cubed, "Invalid color"));
	}
	else
		return (showerror(cubed, "Invalid color"));
	return (1);
}
