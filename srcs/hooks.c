/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:10:06 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 17:09:08 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_closewindow(t_cub3d *game_data)
{
	showerror(game_data, "Window closed by user");
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
		rotate_left(game_data);
	else if (keycode == 'd')
		rotate_right(game_data);
	return (0);
}

int	key_up_hook(int keycode, t_cub3d *game_data)
{
	(void) game_data;
	(void) keycode;
	return (0);
}
