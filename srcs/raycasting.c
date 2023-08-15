/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:13:42 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 16:19:39 by joao-per         ###   ########.fr       */
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
