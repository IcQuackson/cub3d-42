/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:31:02 by quackson          #+#    #+#             */
/*   Updated: 2023/07/10 22:59:14 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	main(void)
{
	t_cub3d	game_data;

	if(!read_map("maps/test.cub"))
	{
		printf("Map is invalid\n");
		//return (0);		
	}
	game_data.mlx = mlx_init();
	game_data.mlx_win = mlx_new_window(game_data.mlx, 800, 600, "Hello world!");
	register_hooks(&game_data);

	mlx_loop(game_data.mlx);
}
