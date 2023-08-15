/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:13:42 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 16:41:22 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * This function performs the DDA algorithm until a wall is hit.
 * It checks if the rc has hit a wall and if so, 
 * it stops the DDA.
 */
void	do_dda(t_cub3d *cubed, t_rc *rc)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (rc->sidedist_x < rc->sidedist_y)
		{
			rc->sidedist_x += rc->deltadist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->sidedist_y += rc->deltadist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (rc->map_y < 0.25 || rc->map_x < 0.25
			|| rc->map_y > cubed->mapinfo.height - 0.25
			|| rc->map_x > cubed->mapinfo.width - 1.25)
			break ;
		else if (cubed->map[rc->map_y][rc->map_x] > '0')
			hit = 1;
	}
}

/*
 * This function calculates the distance to the wall, 
 * the height of the line to draw on the screen, the lowest 
 * and highest pixel to fill in the current stripe, 
 * and the exact position of the wall hit.
 */
void	calculate_height(t_rc *rc, t_player *player)
{
	if (rc->side == 0)
		rc->wall_dist = (rc->sidedist_x - rc->deltadist_x);
	else
		rc->wall_dist = (rc->sidedist_y - rc->deltadist_y);
	rc->line_height = (int)(HEIGHT / rc->wall_dist);
	rc->draw_start = -(rc->line_height) / 2 + HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + HEIGHT / 2;
	if (rc->draw_end >= HEIGHT)
		rc->draw_end = HEIGHT - 1;
	if (rc->side == 0)
		rc->wall_x = player->pos_y + rc->wall_dist * rc->dir_y;
	else
		rc->wall_x = player->pos_x + rc->wall_dist * rc->dir_x;
	rc->wall_x -= floor(rc->wall_x);
}

int	raycasting(t_player *player, t_cub3d *cubed)
{
	t_rc	rc;
	int		x;

	x = 0;
	rc = cubed->rc;
	while (x < WIDTH)
	{
		init_rc_info(x, &rc, player);
		set_dda(&rc, player);
		do_dda(cubed, &rc);
		calculate_height(&rc, player);
		update_texture_pixels(cubed, &cubed->fileinfo, &rc, x);
		x++;
	}
	return (0);
}

void	render_frame(t_cub3d *cubed)
{
	t_image	image;
	int		x;
	int		y;

	image.img = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	image.addr = (int *)mlx_get_data_addr(image.img,
			&image.pixel_bits, &image.size_line, &image.endian);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			set_frame(cubed, &image, x, y);
	}
	mlx_put_image_to_window(cubed->mlx, cubed->win, image.img, 0, 0);
	mlx_destroy_image(cubed->mlx, image.img);
}

int	render_raycast(t_cub3d *cubed)
{
	init_texture_pixels(cubed);
	init_rc(&cubed->rc);
	raycasting(&cubed->player, cubed);
	render_frame(cubed);
	return (0);
}
