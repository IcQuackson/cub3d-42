#include "../includes/cub3d.h"

void	init_img_clean(t_image *image)
{
	image->img = NULL;
	image->addr = NULL;
	image->pixel_bits = 0;
	image->size_line = 0;
	image->endian = 0;
}

void	init_rc(t_rc *rc)
{
	rc->camera_x = 0;
	rc->dir_x = 0;
	rc->dir_y = 0;
	rc->map_x = 0;
	rc->map_y = 0;
	rc->step_x = 0;
	rc->step_y = 0;
	rc->sidedist_x = 0;
	rc->sidedist_y = 0;
	rc->deltadist_x = 0;
	rc->deltadist_y = 0;
	rc->wall_dist = 0;
	rc->wall_x = 0;
	rc->side = 0;
	rc->line_height = 0;
	rc->draw_start = 0;
	rc->draw_end = 0;
}

void	init_mapinfo(t_mapinfo *mapinfo)
{
	mapinfo->path = NULL;
	mapinfo->file = NULL;
	mapinfo->fd = 0;
	mapinfo->line_count = 0;
	mapinfo->height = 0;
	mapinfo->width = 0;
	mapinfo->index_end_of_map = 0;
}

void	init_player(t_player *player)
{
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
}

void	init_structs(t_cub3d *cubed)
{
	cubed->mlx = NULL;
	cubed->win = NULL;
	cubed->map = NULL;
	cubed->texture_pixels = NULL;
	cubed->textures = NULL;
	init_player(&cubed->player);
	init_fileinfo(&cubed->fileinfo);
	init_mapinfo(&cubed->mapinfo);
}