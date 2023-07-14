/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:31:02 by quackson          #+#    #+#             */
/*   Updated: 2023/07/14 14:18:35 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	main(int ac, char **av)
{
	t_cub3d	*game_data;

	if (ac != 2)
	{
		printf("Error: Invalid number of arguments\n");
		return (0);
	}
	game_data = init_data();
	if(!parse_av(game_data, av))
	{
		printf("Error on parsing\n");
		return (0);
	}
	game_data->mlx = mlx_init();
	game_data->mlx_win = mlx_new_window(game_data->mlx,
			800, 600, "Hello world!");
	register_hooks(game_data);
	mlx_loop(game_data->mlx);
	//free_resources(game_data);
}
