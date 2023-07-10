/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:20:52 by quackson          #+#    #+#             */
/*   Updated: 2023/07/10 22:43:22 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 640
# define HEIGHT 480
# define TILE_SIZE 30
# define ESC 65307
# define KEY_PRESS_EVENT 2 
# define KEY_PRESS_MASK 1L
# define DESTROY_EVENT 17

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_cub3d
{
	void	*mlx;
	void	*mlx_win;
	char	**map;
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;

}	t_cub3d;

int		is_valid_char(char c);
int		is_map_closed(char *map);
int		read_map(char *mapfile);
void	register_hooks(t_cub3d *game_data);
void	free_resources(t_cub3d *game_data);
int		handle_closewindow(t_cub3d *game_data);


#endif