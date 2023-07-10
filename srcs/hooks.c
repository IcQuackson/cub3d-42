
#include "../includes/cub3d.h"

void	free_resources(t_cub3d *game_data)
{
	mlx_destroy_window(game_data->mlx, game_data->mlx_win);
	//free_map(game_data->map);
	//free(game_data);
	exit(0);
}

void	register_hooks(t_cub3d *game_data)
{
	mlx_hook(game_data->mlx_win, DESTROY_EVENT, KEY_PRESS_MASK,
		handle_closewindow, game_data);
}

int	handle_closewindow(t_cub3d *game_data)
{
	free_resources(game_data);
	return (0);
}
