#include "../includes/cub3d.h"

/* void	register_hooks(t_cub3d *game_data)
{
	mlx_hook(game_data->mlx_win, DESTROY_EVENT, KEY_PRESS_MASK,
		handle_closewindow, game_data);
} */

void	free_resources(t_cub3d *game_data)
{
	mlx_destroy_window(game_data->mlx, game_data->win);
	mlx_destroy_display(game_data->mlx);
	exit(0);
}

int	handle_closewindow(t_cub3d *game_data)
{
	free_resources(game_data);
	return (0);
}

int	key_down_hook(int keycode, t_cub3d *game_data)
{
	/* if (keycode == ESC)
	{
		destroy(game_data, "");
	} */
	if (keycode == 'w')
	{
		printf("w\n");
		//move_up(game_data, 10);
	}
	else if (keycode == 's')
		printf("s\n");
	else if (keycode == 'a')
	{
		printf("a\n");
		rotate_left(game_data);
		printf("dir_x: %f\n", game_data->player.dir_x);
		printf("dir_y: %f\n", game_data->player.dir_y);
		printf("plane_x: %f\n", game_data->player.plane_x);
		printf("plane_y: %f\n", game_data->player.plane_y);

	}
	else if (keycode == 'd')
	{
		printf("d\n");
		rotate_right(game_data);
	}
	return (0);
}

int	key_up_hook(int keycode, t_cub3d *game_data)
{
	printf("key_up_hook\n");
	(void) game_data;
	(void) keycode;
	return (0);
}
