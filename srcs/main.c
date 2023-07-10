/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:31:02 by quackson          #+#    #+#             */
/*   Updated: 2023/07/10 20:40:57 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

# define MAX_LINE_LENGTH 1000

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void read_map(char *mapfile)
{
	char buffer[MAX_LINE_LENGTH + 1];
	ssize_t bytes_read;
	int fd;

	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening map file");
		return;
	}
	while ((bytes_read = read(fd, buffer, MAX_LINE_LENGTH)) > 0)
	{
		buffer[bytes_read] = '\0';
		printf("%s", buffer);
	}
	if (bytes_read == -1)
		perror("Error reading map file");
	if (close(fd) == -1)
		perror("Error closing map file");
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	printf("%d\n", ft_isalpha('a'));
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	read_map("maps/test.cub");

	mlx_loop(mlx);
}
