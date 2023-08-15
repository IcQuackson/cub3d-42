/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:09:34 by pedgonca          #+#    #+#             */
/*   Updated: 2023/08/15 17:09:37 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_cub3d	cubed;

	if (ac != 2)
		return (showerror(&cubed, "Wrong number of arguments\n"));
	init_structs(&cubed);
	if (!parse_args(&cubed, av))
		return (0);
	cubed.mlx = mlx_init();
	init_textures(&cubed);
	cubed.win = mlx_new_window(cubed.mlx, WIDTH, HEIGHT, "Sussy Cub3d");
	render_raycast(&cubed);
	mlx_hook(cubed.win, KEY_PRESS_EVENT, KEY_PRESS_MASK,
		key_down_hook, &cubed);
	mlx_hook(cubed.win, DESTROY_EVENT, KEY_PRESS_MASK,
		handle_closewindow, &cubed);
	mlx_loop_hook(cubed.mlx, render_raycast, &cubed);
	mlx_loop(cubed.mlx);
}
