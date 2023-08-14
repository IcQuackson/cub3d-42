#include "../includes/cub3d.h"

int freexit(t_cub3d *cubed)
{
	if (!cubed)
		return (0);
	printf("FREEXIT\n");
	if (!cubed->mapinfo.file)
		return (0);
	free(cubed->mapinfo.file);
/* 	if(cubed->tex) */
	return (1);
}

int	showerror(t_cub3d *cubed, char *str)
{
	write(1, "\033[31mError\n\033[0;37m", 18);
	printf("%s", str);
	write(1, "\n", 1);
	freexit(cubed);
	//exit()
	return (0);
}

