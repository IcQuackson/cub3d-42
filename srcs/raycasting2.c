/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:41:15 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 16:41:18 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * The function initializes the texture
 * pixels array in the given cubed struct.
 * 
 * @param cubed The parameter "cubed" is a pointer to
 * a structure of type "t_cub3d".
 * 
 * @return nothing (void).
 */
void	init_texture_pixels(t_cub3d *cbd)
{
	int	i;
	int	j;

	j = -1;
	if (cbd->texture_pixels)
	{
		while (cbd->texture_pixels[++j])
			free(cbd->texture_pixels[j]);
		if (cbd->texture_pixels)
		{
			free(cbd->texture_pixels);
			cbd->texture_pixels = NULL;
		}
	}
	cbd->texture_pixels = ft_calloc(HEIGHT + 1, sizeof * cbd->texture_pixels);
	if (!cbd->texture_pixels)
		return ;
	i = -1;
	while (++i < HEIGHT)
	{
		cbd->texture_pixels[i] = ft_calloc(WIDTH + 1,
				sizeof * cbd->texture_pixels);
		if (!cbd->texture_pixels[i])
			return ;
	}
}

void	get_texture_index(t_cub3d *cubed, t_rc *rc)
{
	if (rc->side == 0)
	{
		if (rc->dir_x < 0)
			cubed->fileinfo.index = 3;
		else
			cubed->fileinfo.index = 2;
	}
	else
	{
		if (rc->dir_y > 0)
			cubed->fileinfo.index = 1;
		else
			cubed->fileinfo.index = 0;
	}
}

void	update_texture_pixels(t_cub3d *cubed, t_fileinfo *tex, t_rc *rc, int x)
{
	int	y;
	int	color;

	get_texture_index(cubed, rc);
	tex->x = (int)(rc->wall_x * tex->size);
	if ((rc->side == 0 && rc->dir_x < 0) || (rc->side == 1 && rc->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / rc->line_height;
	tex->pos = (rc->draw_start - HEIGHT / 2 + rc->line_height / 2) * tex->step;
	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = cubed->textures[tex->index][tex->size * tex->y + tex->x];
		if (tex->index == 0 || tex->index == 2)
			color = (color >> 1) & 8355711;
		if (color > 0)
			cubed->texture_pixels[y][x] = color;
		y++;
	}
}

/*
 * This function initializes the raycasting information.
 * It calculates the x-coordinate in camera space, 
 * the direction of the rc, the current map square the player is in,
 * and the length of the rc from one 
 * x or y-side to the next x or y-side.
 */
void	init_rc_info(int x, t_rc *rc, t_player *player)
{
	init_rc(rc);
	rc->camera_x = 2 * x / (double)WIDTH - 1;
	rc->dir_x = player->dir_x + player->plane_x * rc->camera_x;
	rc->dir_y = player->dir_y + player->plane_y * rc->camera_x;
	rc->map_x = (int)player->pos_x;
	rc->map_y = (int)player->pos_y;
	rc->deltadist_x = fabs(1 / rc->dir_x);
	rc->deltadist_y = fabs(1 / rc->dir_y);
}

/*
 * This function sets the step direction and calculates the side
 distance for the DDA (Digital Differential Analyzer) 
 * algorithm. The DDA algorithm is used to interpolate values
 in a grid over a one-unit interval.
 */
void	set_dda(t_rc *rc, t_player *player)
{
	if (rc->dir_x < 0)
	{
		rc->step_x = -1;
		rc->sidedist_x = (player->pos_x - rc->map_x) * rc->deltadist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->sidedist_x = (rc->map_x + 1.0 - player->pos_x) * rc->deltadist_x;
	}
	if (rc->dir_y < 0)
	{
		rc->step_y = -1;
		rc->sidedist_y = (player->pos_y - rc->map_y) * rc->deltadist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->sidedist_y = (rc->map_y + 1.0 - player->pos_y) * rc->deltadist_y;
	}
}
