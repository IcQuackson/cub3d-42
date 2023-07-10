/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:51:00 by joao-per          #+#    #+#             */
/*   Updated: 2023/07/11 00:51:00 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void check_map_dimensions(int x, int oldx, int y)
{
	if (x != oldx && y > 0)
	{
		printf("Map is not rectangular\n");
		exit(1);
	}
}

void check_map_validity(int x, int y)
{
	if (y == 0 || x == 0)
	{
		printf("Map is not correct or not well formatted\n");
		exit(1);
	}
}