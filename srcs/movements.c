
#include "../includes/cub3d.h"

# define PI 3.14159265358979323846

double degree_to_rad(int degree)
{
	return (degree * (M_PI / 180));
}

void rotate_left(t_cub3d *cubed)
{
	int ROT_SPEED = degree_to_rad(5);
	// rotate 1 degree

	// convert dir_x and dir_y to angle in degree
	// double angle = atan2(cubed->player.dir_y, cubed->player.dir_x) * 180 / PI;

	cubed->player.dir_x = cubed->player.dir_x * cos(-ROT_SPEED)
		- cubed->player.dir_y * sin(-ROT_SPEED);
	cubed->player.dir_y = cubed->player.dir_x * sin(-ROT_SPEED) +
		cubed->player.dir_y * cos(-ROT_SPEED);
	/* cubed->player.plane_x = cubed->player.plane_x * cos(-ROT_SPEED)
		- cubed->player.plane_y * sin(-ROT_SPEED);
	cubed->player.plane_y = cubed->player.plane_x * sin(-ROT_SPEED) +
		cubed->player.plane_y * cos(-ROT_SPEED); */
}

void rotate_right(t_cub3d *cubed)
{
	int ROT_SPEED = 5;
	cubed->player.dir_x = cubed->player.dir_x * cos(ROT_SPEED)
		- cubed->player.dir_y * sin(ROT_SPEED);
	cubed->player.dir_y = cubed->player.dir_x * sin(ROT_SPEED) +
		cubed->player.dir_y * cos(ROT_SPEED);
	/* cubed->player.plane_x = cubed->player.plane_x * cos(ROT_SPEED)
		- cubed->player.plane_y * sin(ROT_SPEED);
	cubed->player.plane_y = cubed->player.plane_x * sin(ROT_SPEED) +
		cubed->player.plane_y * cos(ROT_SPEED); */
}
