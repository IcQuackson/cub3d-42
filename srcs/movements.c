
#include "../includes/cub3d.h"

# define PI 3.14159265358979323846

double degree_to_rad(int degree)
{
	return (degree * (PI / 180));
}

void rotate_left(t_cub3d *cubed)
{
	double rotSpeed = 0.05;

	double oldDirX = cubed->player.dir_x;
	cubed->player.dir_x = cubed->player.dir_x * cos(-rotSpeed) - cubed->player.dir_y * sin(-rotSpeed);
	cubed->player.dir_y = oldDirX * sin(-rotSpeed) + cubed->player.dir_y * cos(-rotSpeed);
	
	double oldPlaneX = cubed->player.plane_x;
	cubed->player.plane_x = cubed->player.plane_x * cos(-rotSpeed) - cubed->player.plane_y * sin(-rotSpeed);
	cubed->player.plane_y = oldPlaneX * sin(-rotSpeed) + cubed->player.plane_y * cos(-rotSpeed);
}

void rotate_right(t_cub3d *cubed)
{
	double rotSpeed = 0.05;

      double oldDirX = cubed->player.dir_x;
      cubed->player.dir_x = cubed->player.dir_x * cos(rotSpeed) - cubed->player.dir_y * sin(rotSpeed);
      cubed->player.dir_y = oldDirX * sin(rotSpeed) + cubed->player.dir_y * cos(rotSpeed);
      
	  double oldPlaneX = cubed->player.plane_x;
      cubed->player.plane_x = cubed->player.plane_x * cos(rotSpeed) - cubed->player.plane_y * sin(rotSpeed);
      cubed->player.plane_y = oldPlaneX * sin(rotSpeed) + cubed->player.plane_y * cos(rotSpeed);
}

void move_forward(t_cub3d *cubed)
{
	double moveSpeed = 0.1;
	double next_pos_x = cubed->player.pos_x + cubed->player.dir_x * moveSpeed;
	double next_pos_y = cubed->player.pos_y + cubed->player.dir_y * moveSpeed;

	// Check if the next position is inside a wall
	if (cubed->map[(int)next_pos_y][(int)next_pos_x] == '0') {
		cubed->player.pos_x = next_pos_x;
		cubed->player.pos_y = next_pos_y;
	}
}

void move_back(t_cub3d *cubed)
{
	double moveSpeed = 0.1;
	double next_pos_x = cubed->player.pos_x - cubed->player.dir_x * moveSpeed;
	double next_pos_y = cubed->player.pos_y - cubed->player.dir_y * moveSpeed;

	// Check if the next position is inside a wall
	if (cubed->map[(int)next_pos_y][(int)next_pos_x] == '0') {
		cubed->player.pos_x = next_pos_x;
		cubed->player.pos_y = next_pos_y;
	}
}
