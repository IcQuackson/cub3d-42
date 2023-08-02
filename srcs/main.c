/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:31:02 by quackson          #+#    #+#             */
/*   Updated: 2023/08/02 04:35:55 by joao-per         ###   ########.fr       */
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
	cubed.win = mlx_new_window(cubed.mlx, WIDTH, HEIGHT, "Sussy Cub3d");
	init_textures(&cubed);
	render_raycast(&cubed);
	mlx_loop_hook(cubed.mlx, render_raycast, &cubed);
	mlx_loop(cubed.mlx);
}
