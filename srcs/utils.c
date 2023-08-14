#include "../includes/cub3d.h"


void	free_fileinfo(t_fileinfo *fileinfo)
{
	if (fileinfo->ceiling)
		free(fileinfo->ceiling);
	if (fileinfo->floor)
		free(fileinfo->floor);
	if (fileinfo->north)
		free(fileinfo->north);
	if (fileinfo->south)
		free(fileinfo->south);
	if (fileinfo->west)
		free(fileinfo->west);
	if (fileinfo->east)
		free(fileinfo->east);
}

void freexit(t_cub3d *cubed)
{
	if (!cubed)
		return ;
	printf("FREEXIT\n");
	free_fileinfo(&cubed->fileinfo);
	if (cubed->mapinfo.file)
		free(cubed->mapinfo.file);
/* 	if(cubed->tex) */
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

