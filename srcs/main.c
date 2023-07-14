/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:31:02 by quackson          #+#    #+#             */
/*   Updated: 2023/07/14 23:45:47 by quackson         ###   ########.fr       */
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
	if (!is_valid_file(argv[1]))
	{
		printf("Error\n");
		free_resources(game_data);
		return (0);
	}
	if (!get_file_data(game_data, argv[1]))
	{
		printf("Error\n");
		free_resources(game_data);
		return (0);
	}
	else
		printf("Valid Map\n");
	//game_data->mlx = mlx_init();
	//game_data->mlx_win = mlx_new_window(game_data->mlx,
	//		800, 600, "Hello world!");
	//register_hooks(game_data);
	//mlx_loop(game_data->mlx);
	free_resources(game_data);
}
