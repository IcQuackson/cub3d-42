#include "../includes/cub3d.h"

int check_folder(char *av)
{
	int i;

	i = 0;
	while (av[i] != '\0')
		i++;
	if (av[i - 1] == '/' || av[i - 1] == '.')
		return (1);
	return (0);
}

int check_cub(char *av)
{
	int i;

	i = 0;
	while (av[i] != '\0')
		i++;
	if (av[i - 1] != 'b' || av[i - 2] != 'u' || av[i - 3] != 'c' || av[i - 4] != '.')
		return (0);
	return (1);
}

int check_xpm(char *av)
{
	int i;

	i = 0;
	while (av[i] != '\0')
		i++;
	if (av[i - 1] != 'm' || av[i - 2] != 'p' || av[i - 3] != 'x' || av[i - 4] != '.')
		return (0);
	return (1);
}

int	check_file(char *av, int flag)
{
	int	fd;

	if (check_folder(av))
		return (0);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	if (flag && !check_cub(av))
		return (0);
	if (!flag && !check_xpm(av))
		return (0);
	return (1);
}

int parse_av(t_cub3d *cubed, char **av)
{
	if (!check_file(av[1], 1))
		return (0);
	if (parse_data(cubed, av) == 0)
		return (0);
	return (1);
}