#include "../includes/cub3d.h"

int	get_num_lines(char *map_file)
{
	int		fd;
	char	*line;
	int		num_lines;

	num_lines = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		//printf("%s\n", line);
		num_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (num_lines);
}

int	fill_map(t_cub3d *cubed, int i)
{
	char	*line;
	int		row;
	int 	column;

	row = 0;
	column = 0;
	line = get_next_line(cubed->map_data.fd);
	while (line != NULL)
	{
		cubed->map_data.grid[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!cubed->map_data.grid[row])
			return (0);
		while (line[i])
			cubed->map_data.grid[row][column++] = line[i++];
		cubed->map_data.grid[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(cubed->map_data.fd);
	}
	cubed->map_data.grid[row] = NULL;
	return (1);
}

// grid
// NO
// rgb
// mapa

int	parse_data(t_cub3d *cubed, char *file)
{
	int	i;

	i = 0;
	cubed->map_data.path = file;
	cubed->map_data.line_nbr = get_num_lines(file);
	cubed->map_data.grid = ft_calloc(sizeof(char *),
			cubed->map_data.line_count + 1);
	if (!(cubed->map_data.grid))
		return (0);
	cubed->map_data.fd = open(file, O_RDONLY);
	if (cubed->map_data.fd < 0)
		return (0);
	fill_map(cubed, i);
	close(cubed->map_data.fd);
	return (1);
}
