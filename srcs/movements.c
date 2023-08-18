/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:47:18 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/18 10:52:59 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_left(t_cub3d *cubed)
{
	double	rotspeed;
	double	olddirx;
	double	oldplanex;

	oldplanex = cubed->player.plane_x;
	olddirx = cubed->player.dir_x;
	rotspeed = 0.05;
	cubed->player.dir_x = cubed->player.dir_x * cos(-rotspeed)
		- cubed->player.dir_y * sin(-rotspeed);
	cubed->player.dir_y = olddirx * sin(-rotspeed)
		+ cubed->player.dir_y * cos(-rotspeed);
	cubed->player.plane_x = cubed->player.plane_x
		* cos(-rotspeed) - cubed->player.plane_y * sin(-rotspeed);
	cubed->player.plane_y = oldplanex * sin(-rotspeed)
		+ cubed->player.plane_y * cos(-rotspeed);
}

void	rotate_right(t_cub3d *cubed)
{
	double	rotspeed;
	double	olddirx;
	double	oldplanex;

	rotspeed = 0.05;
	olddirx = cubed->player.dir_x;
	oldplanex = cubed->player.plane_x;
	cubed->player.dir_x = cubed->player.dir_x
		* cos(rotspeed) - cubed->player.dir_y * sin(rotspeed);
	cubed->player.dir_y = olddirx * sin(rotspeed)
		+ cubed->player.dir_y * cos(rotspeed);
	cubed->player.plane_x = cubed->player.plane_x
		* cos(rotspeed) - cubed->player.plane_y * sin(rotspeed);
	cubed->player.plane_y = oldplanex * sin(rotspeed)
		+ cubed->player.plane_y * cos(rotspeed);
}

void	move_forward(t_cub3d *cubed)
{
	double	movespeed;
	double	next_pos_x;
	double	next_pos_y;

	movespeed = 0.1;
	next_pos_x = cubed->player.pos_x + cubed->player.dir_x * movespeed;
	next_pos_y = cubed->player.pos_y + cubed->player.dir_y * movespeed;
	if (cubed->map[(int)next_pos_y][(int)next_pos_x] == '0')
	{
		cubed->player.pos_x = next_pos_x;
		cubed->player.pos_y = next_pos_y;
	}
}

void	move_back(t_cub3d *cubed)
{
	double	movespeed;
	double	next_pos_x;
	double	next_pos_y;

	movespeed = 0.1;
	next_pos_x = cubed->player.pos_x - cubed->player.dir_x * movespeed;
	next_pos_y = cubed->player.pos_y - cubed->player.dir_y * movespeed;
	if (cubed->map[(int)next_pos_y][(int)next_pos_x] == '0')
	{
		cubed->player.pos_x = next_pos_x;
		cubed->player.pos_y = next_pos_y;
	}
}

void	strafe_left(t_cub3d *cubed)
{
	double	movespeed;
	double	next_pos_x;
	double	next_pos_y;

	movespeed = 0.1;
	next_pos_x = cubed->player.pos_x - cubed->player.plane_x * movespeed;
	next_pos_y = cubed->player.pos_y - cubed->player.plane_y * movespeed;
	if (cubed->map[(int)next_pos_y][(int)next_pos_x] == '0')
	{
		cubed->player.pos_x = next_pos_x;
		cubed->player.pos_y = next_pos_y;
	}
}
