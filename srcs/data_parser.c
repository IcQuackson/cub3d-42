#include "../includes/cub3d.h"

int	get_num_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		showerror(NULL, "File not found");
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}
void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	store_map(int row, int column, int i, t_cub3d *cubed)
{
	char	*line;

	line = get_next_line(cubed->mapinfo.fd);
	while (line != NULL)
	{
		cubed->mapinfo.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!cubed->mapinfo.file[row])
			return (free_tab((void **)cubed->mapinfo.file));
		while (line[i] != '\0')
			cubed->mapinfo.file[row][column++] = line[i++];
		cubed->mapinfo.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(cubed->mapinfo.fd);
	}
	cubed->mapinfo.file[row] = NULL;
}

void	parse_data(char *path, t_cub3d *cubed)
{
	int		row;
	int		i;
	int		column;

	i = 0;
	row = 0;
	column = 0;
	cubed->mapinfo.path = path;
	cubed->mapinfo.line_count = get_num_lines(path);
	cubed->mapinfo.file = ft_calloc(cubed->mapinfo.line_count + 1, sizeof(char *));
	if (!(cubed->mapinfo.file))
		return ;
	cubed->mapinfo.fd = open(path, O_RDONLY);
	if (cubed->mapinfo.fd < 0)
		showerror(cubed, "Bad Open");
	store_map(row, column, i, cubed);
	close(cubed->mapinfo.fd);
}