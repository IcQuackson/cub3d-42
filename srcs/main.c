/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:31:02 by quackson          #+#    #+#             */
/*   Updated: 2023/07/15 17:42:01 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_double_char(char **ptr)
{
	while (*ptr)
	{
		printf("%s\n", *ptr);
		ptr++;
	}
}

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
	{
		print_double_char(game_data->map);
		printf("height: %d\n", game_data->map_data.height);
		printf("Valid Map\n");
	}
	//game_data->mlx = mlx_init();
	//game_data->mlx_win = mlx_new_window(game_data->mlx,
	//		800, 600, "Hello world!");
	//register_hooks(game_data);
	//mlx_loop(game_data->mlx);
	free_resources(game_data);
}
