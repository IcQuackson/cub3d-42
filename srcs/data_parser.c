#include "../includes/cub3d.h"

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

int	get_num_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (showerror(NULL, "Bad Open"));
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

int	parse_data(char *path, t_cub3d *cbd)
{
	int		row;
	int		i;
	int		column;

	i = 0;
	row = 0;
	column = 0;
	cbd->mapinfo.path = path;
	cbd->mapinfo.line_count = get_num_lines(path);
	if (cbd->mapinfo.line_count == 0)
		return (0);
	cbd->mapinfo.file = ft_calloc(cbd->mapinfo.line_count + 1, sizeof(char *));
	if (!(cbd->mapinfo.file))
		return (showerror(cbd, "Bad Allocation"));
	cbd->mapinfo.fd = open(path, O_RDONLY);
	if (cbd->mapinfo.fd < 0)
		return (showerror(cbd, "Bad Open"));
	store_map(row, column, i, cbd);
	close(cbd->mapinfo.fd);
	return (1);
}
