/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:20:52 by quackson          #+#    #+#             */
/*   Updated: 2023/07/11 18:07:25 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MAX_LINE_LENGTH 1000
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

typedef struct s_map
{
	char	**grid;
	int		width;
	int 	line_count;
	int		height;
	int		player_x;
	int		player_y;
	char	player_orientation;
}	t_map;

typedef struct s_scene
{
	int		num_lines;
	char	**lines;
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	int		ceil_rgb[3];
	int		floor_rgb[3];
	t_map	*map;
}	t_scene;

typedef struct s_cub3d
{
	void	*mlx;
	void	*mlx_win;
	char	**map;
	t_scene	*scene;
	t_map	*map;

}	t_cub3d;




int		is_valid_char(char c);
int		is_map_closed(char *map);
int		read_map(char *mapfile);
void	register_hooks(t_cub3d *game_data);
void	free_resources(t_cub3d *game_data);
int		handle_closewindow(t_cub3d *game_data);
char	*get_next_line(int fd);
int		is_line_wall(char *line);
int		is_line_closed(char *line);
int		is_map_closed(char *mapfile);
int		is_valid_char(char c);
int		read_map(char *mapfile);
void	get_x_and_y(t_map *map, char *filename);
void	store_map(t_map *map, char *filename);
void	check_map_dimensions(int x, int oldx, int y);
void	check_map_validity(int x, int y);
int		get_scene_data(t_cub3d *game_data, char *map_file);
t_cub3d	*init_data(void);
#endif