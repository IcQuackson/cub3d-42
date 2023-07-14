/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:31:02 by quackson          #+#    #+#             */
/*   Updated: 2023/07/14 18:15:16 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	main(int argc, char **argv)
{
	t_cub3d	*game_data;

	if (argc != 2)
	{
		printf("Error\n");
		return (0);
	}
	game_data = init_data();
	if (!is_valid_file(game_data, argv[1]))
	{
		printf("Error\n");
		return (0);
	}
	else
		printf("Valid Map\n");
	//game_data->mlx = mlx_init();
	//game_data->mlx_win = mlx_new_window(game_data->mlx,
	//		800, 600, "Hello world!");
	//register_hooks(game_data);
	//mlx_loop(game_data->mlx);
	//free_resources(game_data);
}
