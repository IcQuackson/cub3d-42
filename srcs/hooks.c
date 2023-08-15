/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:10:06 by joao-per          #+#    #+#             */
/*   Updated: 2023/08/15 16:10:07 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* void	register_hooks(t_cub3d *game_data)
{
	mlx_hook(game_data->mlx_win, DESTROY_EVENT, KEY_PRESS_MASK,
		handle_closewindow, game_data);
} */

int	handle_closewindow(t_cub3d *game_data)
{
	mlx_destroy_window(game_data->mlx, game_data->win);
	mlx_destroy_display(game_data->mlx);
	freexit(game_data);
	free(game_data->mlx);
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
