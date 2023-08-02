/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-per <joao-per@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:20:52 by quackson          #+#    #+#             */
/*   Updated: 2023/08/02 04:36:58 by joao-per         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define XPM 0
# define CUB 1
# define MAX_LINE_LENGTH 1000
# define WIDTH 1920
# define HEIGHT 1080
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
# include <math.h>

typedef struct s_image
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_fileinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_fileinfo;

typedef struct s_minimap
{
	char	**map;
	t_img	*img;
	int		size;
	int		offset_x;
	int		offset_y;
	int		view_dist;
	int		tile_size;
}	t_minimap;

typedef struct s_mapinfo
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
}	t_mapinfo;

typedef struct s_rc
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_rc;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_cubed
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_mapinfo	mapinfo;
	char		**map;
	t_player	player;
	t_rc		rc;
	int			**texture_pixels;
	int			**textures;
	t_fileinfo	fileinfo;
	t_img		minimap;
}	t_cub3d;

/*					Map_Check					*/
size_t			find_biggest_wall(t_mapinfo *map, int i);
int				check_map(t_cub3d *cubed);
int				check_top_or_bottom(char **map_tab, int i, int j);
int				check_map_sides(t_mapinfo *map, char **map_tab);
int				check_chars(t_cub3d *cubed, char **map_tab);
int				check_pos_is_valid(t_cub3d *cubed, char **map_tab);
int				check_pos(t_cub3d *cubed, char **map_tab);
int				check_end_of_map(t_mapinfo *map);
int				check_map_validity(t_cub3d *cubed, char **map_tab);

/*					File_Parser					*/
int				parse_args(t_cub3d *cubed, char **av);
int				check_file(char *arg, int type);
int				is_xpm_file(char *arg);
int				is_cub_file(char *arg);
int				is_folder(char *arg);

/*					Data_Parser					*/
void			parse_data(char *path, t_cub3d *cubed);
void			store_map(int row, int column, int i, t_cub3d *cubed);
int				get_num_lines(char *path);
void			store_map(int row, int column, int i, t_cub3d *cubed);

/*					Init						*/
void			init_img_clean(t_image *image);
void			init_rc(t_rc *rc);
void			init_player(t_player *player);
void			init_fileinfo(t_fileinfo *fileinfo);
void			init_mapinfo(t_mapinfo *mapinfo);
void			init_structs(t_cub3d *cubed);

/*					Init_Textures				*/
void			init_textures(t_cub3d *cubed);
int				*xpm_to_image(t_cub3d *cubed, char *path);
int				*set_rgb(char *line);
int				fill_color_textures(t_cub3d *cubed, t_fileinfo *textures, char *line, int j);

/*				Texture_Checker				*/
unsigned long	convert_rgb(int *rgb_tab);
int				check_textures_validity(t_cub3d *cubed, t_fileinfo *textures);
int				check_rgb_values(int *rgb);

/*				Textures				*/
int				get_file_data(t_cub3d *cubed, char **map);
int				fill_dir_and_text(t_cub3d *cubed, char **map, int i, int j);
int				fill_direction_textures(t_fileinfo *textures, char *line, int j);
char			*get_texture_path(char *line, int j);

/*				Raycasting				*/
void			get_texture_index(t_cub3d *cubed, t_rc *rc);
void			init_texture_pixels(t_cub3d *cubed);
void			update_texture_pixels(t_cub3d *cubed, t_fileinfo *tex, t_rc *rc, int x);
void			init_rc_info(int x, t_rc *rc, t_player *player);
void			set_dda(t_rc *rc, t_player *player);
void			do_dda(t_cub3d *cubed, t_rc *rc);
void			calculate_height(t_rc *rc, t_player *player);
void			set_image_pixel(t_image *image, int x, int y, int color);
void			set_frame(t_cub3d *cubed, t_image *image, int x, int y);
void			render_frame(t_cub3d *cubed);
int				raycasting(t_player *player, t_cub3d *cubed);
int				render_raycast(t_cub3d *cubed);

/*				Player				*/
void			init_direction(t_player *player);

/*				Create_Map				*/
void			change_space_into_wall(t_cub3d *cubed);
int				count_map_lines(t_cub3d *cubed, char **file, int i);
int				fill_map(t_mapinfo *mapinfo, char **map_tab, int index);
int				get_map_info(t_cub3d *cubed, char **file, int i);
int				create_map(t_cub3d *cubed, char **file, int i);

/*				Utils				*/
int				showerror(t_cub3d *cubed, char *str);
void			free_tab(void **tab);
char			*get_next_line(int fd);
#endif
