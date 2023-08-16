/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:10:06 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/16 13:19:42 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_closewindow(t_cub3d *game_data)
{
	freexit(game_data);
	exit(0);
}

int	key_down_hook(int keycode, t_cub3d *game_data)
{
	if (keycode == ESC)
		handle_closewindow(game_data);
	if (keycode == 'w')
		move_forward(game_data);
	else if (keycode == 's')
		move_back(game_data);
	else if (keycode == 'a')
		strafe_left(game_data);
	else if (keycode == 'd')
		strafe_right(game_data);
	else if (keycode == XK_Left)
		rotate_left(game_data);
	else if (keycode == XK_Right)
		rotate_right(game_data);
	return (0);
}

int	key_up_hook(int keycode, t_cub3d *game_data)
{
	(void) game_data;
	(void) keycode;
	return (0);
}
