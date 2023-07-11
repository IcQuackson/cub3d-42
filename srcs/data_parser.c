#include "../includes/cub3d.h"

void fill_tab(int row, int column, int i, t_cub3d cubed)
{
	char *line;

	line = get_next_line(cubed->mapinfo.fd);
	while (line != NULL)
	{
		cubed->map.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!cubed->map.file[row])
		{
			printf("Error");
			return ;
		}
		while (line[i] != '\0')
			cubed->map.file[row][column++] = line[i++];
		cubed->map.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(cubed->map.fd);
	}
	cubed->map.file[row] = NULL;
}

void parse_data(char *path, t_cub3d cubed)
{
	int row;
	int i;
	size_t column;

	i = 0;
	row = 0;
	column = 0;
	cubed->map.fd = open(path, O_RDONLY);
	if (cubed->mapinfo.fd < 0)
	{
		printf("Error");
		return ;
	}
	else
	{
		cubed->map.line_count = get_num_lines(path);
		cubed->map.file = ft_calloc(cubed->map.line_count + 1, sizeof(char *));
		fill_tab(row, column, i, cubed);
		close(cubed->mapinfo.fd);
	}
}