#include "../includes/cub3d.h"

int	showerror(t_cub3d *cubed, char *str)
{
	(void)cubed;
	write(1, "\033[31mError\n\033[0;37m", 18);
	printf("%s", str);
	write(1, "\n", 1);
	//freexit(cubed);
	return (0);
}