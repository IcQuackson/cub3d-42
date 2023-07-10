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