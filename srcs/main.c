/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:31:02 by quackson          #+#    #+#             */
/*   Updated: 2023/08/01 23:19:02 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_args(t_cub3d *cubed, char **av)
{
	if (check_file(av[1], 1) == 1)
		return (0);
	parse_data(av[1], cubed);
	if (get_file_data(cubed, cubed->mapinfo.file) == 1)
		return (0);
	if (check_map_validity(cubed, cubed->map) == 1)
		return (0);
	if (check_textures_validity(cubed, &cubed->fileinfo) == 1)
		return (0);
	init_player_direction(cubed);
	return (1);
}

int	main(int ac, char **av)
{
	t_cub3d	cubed;

	if (ac != 2)
		return (showerror(&cubed, "Wrong number of arguments\n"));
	init_structs(&cubed);
	if (!parse_args(&cubed, av))
		return (0);
	cubed.mlx = mlx_init();
	cubed.win = mlx_new_window(cubed.mlx, WIN_WIDTH, WIN_HEIGHT, "Sussy Cub3d");
	init_textures(&cubed);
	render_raycast(&cubed);
	mlx_loop_hook(cubed.mlx, render_raycast, &cubed);
	mlx_loop(cubed.mlx);
}
