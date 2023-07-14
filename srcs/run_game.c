#include "../includes/cub3d.h"

#define SQUARE_SIZE 10

void put_pixel(t_cub3d *game_data, int x, int y, int color)
{
	mlx_pixel_put(game_data->mlx, game_data->mlx_win, x, y, color);
}

void draw_chessboard(t_cub3d *game_data)
{
    int num_squares_x = 10;
    int num_squares_y = 10;

    int start_x = 0; // Starting x-coordinate of the chessboard
    int start_y = HEIGHT - (num_squares_y * SQUARE_SIZE); // Starting y-coordinate of the chessboard
	printf("start y: %d\n", start_y);
    for (int row = 0; row < num_squares_y; row++) {
        for (int col = 0; col < num_squares_x; col++) {
            int square_x = start_x + (col * SQUARE_SIZE);
            int square_y = start_y + (row * SQUARE_SIZE);

            // Alternate the colors based on the square position
            int is_even_square = (row + col) % 2 == 0;

            if (is_even_square) {
                // White square
                for (int y = square_y; y < square_y + SQUARE_SIZE; y++) {
                    for (int x = square_x; x < square_x + SQUARE_SIZE; x++) {
                        put_pixel(game_data, x, y, 0xFFFFFF); // White color
                    }
                }
            } else {
                // Black square
                for (int y = square_y; y < square_y + SQUARE_SIZE; y++) {
                    for (int x = square_x; x < square_x + SQUARE_SIZE; x++) {
                        put_pixel(game_data, x, y, 0x000000); // Black color
                    }
                }
            }
        }
    }
}

void	run_game(t_cub3d *game_data)
{
	// Draw the chessboard pattern on the window
    draw_chessboard(game_data);
	// Start the main event loop
	mlx_loop(game_data->mlx);
	return ;
}
