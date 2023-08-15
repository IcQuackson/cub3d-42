/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:09:34 by pedgonca          #+#    #+#             */
/*   Updated: 2023/08/15 18:04:39 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_cub3d	cubed;

	if (ac != 2)
	{
		printf("\033[31mError\n\033[0;37mWrong number of arguments\n");
		return (0);
	}
	init_structs(&cubed);
	if (!parse_args(&cubed, av))
		return (0);
	cubed.mlx = mlx_init();
	init_textures(&cubed);
	cubed.win = mlx_new_window(cubed.mlx, WIDTH, HEIGHT, "Sussy Cub3d");
	render_raycast(&cubed);
	start_program();
	mlx_hook(cubed.win, KEY_PRESS_EVENT, KEY_PRESS_MASK,
		key_down_hook, &cubed);
	mlx_hook(cubed.win, DESTROY_EVENT, KEY_PRESS_MASK,
		handle_closewindow, &cubed);
	mlx_loop_hook(cubed.mlx, render_raycast, &cubed);
	mlx_loop(cubed.mlx);
}
