#include "../includes/cub3d.h"

void	get_player_data(t_player *player)
{
	if (player->dir == 'N')
	{
		player->x = 0;
		player->y = -1;
	}
	else if (player->dir == 'S')
	{
		player->x = 0;
		player->y = 1;
	}
	else if (player->dir == 'W')
	{
		player->x = -1;
		player->y = 0;
	}
	else if (player->dir == 'E')
	{
		player->x = 1;
		player->y = 0;
	}
	else
		return (0);
}
