/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:31:02 by quackson          #+#    #+#             */
/*   Updated: 2023/07/11 11:18:04 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	main(void)
{
	t_cub3d	*game_data;

	game_data = init_data();
	if (!(game_data && get_textures(game_data, "maps/test.cub")))
	{
		free_resources(game_data);
		return (0);
	}
	/* if (!read_map("maps/test.cub"))
	{
		printf("Map is invalid\n");
		//return (0);		
	} */
	mlx_loop(game_data->mlx);
	//free_resources(game_data);
}
