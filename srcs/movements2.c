/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:53:14 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/18 10:53:21 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	strafe_right(t_cub3d *cubed)
{
	double	movespeed;
	double	next_pos_x;
	double	next_pos_y;

	movespeed = 0.1;
	next_pos_x = cubed->player.pos_x + cubed->player.plane_x * movespeed;
	next_pos_y = cubed->player.pos_y + cubed->player.plane_y * movespeed;
	if (cubed->map[(int)next_pos_y][(int)next_pos_x] == '0')
	{
		cubed->player.pos_x = next_pos_x;
		cubed->player.pos_y = next_pos_y;
	}
}
