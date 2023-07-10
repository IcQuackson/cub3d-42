/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:31:02 by quackson          #+#    #+#             */
/*   Updated: 2023/07/10 22:46:02 by quackson         ###   ########.fr       */
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

int	main(void)
{
	t_data	img;

	t_cub3d game_data;

	printf("%d\n", ft_isalpha('a'));
	
	if(!read_map("maps/test.cub"))
	{
		printf("Map is invalid\n");
		//return (0);		
	}
	game_data.mlx = mlx_init();
	game_data.mlx_win = mlx_new_window(game_data.mlx, 1920, 1080, "Hello world!");
	register_hooks(&game_data);
	img.img = mlx_new_image(game_data.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(game_data.mlx, game_data.mlx_win, img.img, 0, 0);
	mlx_loop(game_data.mlx);
}
