#include "../includes/cub3d.h"

#include <math.h>

# define ESC 65307
# define KEY_PRESS_EVENT 2 
# define KEY_PRESS_MASK 1L
# define DESTROY_EVENT 17
#define SQUARE_SIZE 15
#define screenWidth 640
#define screenHeight 480
#define PI 3.1415926535


double posX = 22, posY = 12;  //x and y start position
double dirX = -1, dirY = 0; //initial direction vector
double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

double time = 0; //time of current frame
double oldTime = 0; //time of previous frame


#include <math.h>

void put_pixel(t_cub3d *game_data, int x, int y, int color)
{
	mlx_pixel_put(game_data->mlx, game_data->mlx_win, x, y, color);
}

void draw_line_aux(t_cub3d *game_data, int x0, int y0, int x1, int y1)  
{  
    int dx, dy, p, x, y;  
    dx=x1-x0;  
    dy=y1-y0;  
    x=x0;  
    y=y0;  
    p=2*dy-dx;  
    while(x<x1)  
    {  
        if(p>=0)  
        {  
			put_pixel(game_data, x, y, 0xADD8E6);
            y=y+1;  
            p=p+2*dy-2*dx;  
        }  
        else  
        {  
			put_pixel(game_data, x, y, 0xADD8E6);
            p=p+2*dy;}  
            x=x+1;  
        }  
}  

void	draw_square(t_cub3d *game_data, int x, int y, int color, int square_size, int border_flag)
{
	int i;
	int j;

	i = 0;
	while (i < square_size)
	{

		j = 0;
		while (j < square_size)
		{
			put_pixel(game_data, x + i, y + j, color);
			if (border_flag && i == 0)
				put_pixel(game_data, x + i, y + j, 0xFF0000);
			else if (border_flag && j == square_size - 1)
				put_pixel(game_data, x + i, y + j, 0x008000);
			j++;
		}
		i++;
	}
}

int	is_wall(int x, int y, int minimap_offset, t_cub3d *game_data)
{
	(void) minimap_offset;

	char map[15][10] =
	{
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
        {'1', '1', '1', '1', '1', '0', 'S', '1', '0', '1'},
        {'1', '1', '1', '1', '1', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '0', '0', '0', '0', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
        {'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
        {'1', '1', '0', '0', '0', '0', '0', '1', '1', '1'},
        {'1', '1', '1', '0', '1', '0', '1', '1', '1', '1'},
        {'1', '1', '1', '0', '1', '0', '1', '1', '1', '1'},
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
    };
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	if (x < 0 || x >= 15 * game_data->tile_size || y < 0 || y >= 10 * game_data->tile_size)
		return (0);
	return (map[x / game_data->tile_size][y / game_data->tile_size] == '1');
}

void draw_line(t_cub3d *game_data, int x0, int y0, int distance, float angle, int color)
{
	int x1 = x0 + (float) (distance * cos(angle)); // Calculate the ending point (x-coordinate)
	int y1 = y0 + (float) (distance * sin(angle)); // Calculate the ending point (y-coordinate)

	int dx = x1 - x0;
	int dy = y1 - y0;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	float xIncrement = (float)dx / steps;
	float yIncrement = (float)dy / steps;

	float x = x0;
	float y = y0;

	//printf("x0: %d\n", x0);
	//printf("y0: %d\n", y0);
	//printf("x1: %d\n", x1);
	//printf("y1: %d\n", y1);

	for (int i = 0; i <= steps && !is_wall(y, x, 0, game_data); i++) {
		put_pixel(game_data, (int)x, (int)y, color); // Set the pixel color to white (you can change this)
		x += xIncrement;
		y += yIncrement;
	}
}

float	degToRad(int a)
{
	return (a * PI / 180.0);
}

float distance(int ax, int ay, int bx, int by, int ang)
{
	return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);
}


int calculateMinimapSquareSize(int mapWidth, int mapHeight, t_cub3d *game_data) {
    int squareWidth = 0.3 * HEIGHT / mapHeight;
    int squareHeight = 0.3 * WIDTH / mapWidth;
	
    game_data->tile_size = (squareWidth > squareHeight) ? squareWidth : squareHeight;
	return (game_data->tile_size);
}

int	is_player_coord(int x, int y, t_cub3d *game_data)
{
	return (x == game_data->map_data.player_x && y == game_data->map_data.player_y);
}

void	cast_fov_rays(t_cub3d *game_data, int color)
{
	int i;

	i = -30;
	while (i <= 30)
	{
		if (color != 0x000000 && i == 0)
			draw_line(game_data, game_data->map_data.player_y, game_data->map_data.player_x, 100, game_data->player_angle + degToRad(i), 0xFF0000);
		else
			draw_line(game_data, game_data->map_data.player_y, game_data->map_data.player_x, 100, game_data->player_angle + degToRad(i), color);
		//game_data->player_angle += degToRad(1);
		i++;
	}
}

void	erase_player(t_cub3d *game_data)
{
	cast_fov_rays(game_data, 0x000000);
	draw_square(game_data, game_data->map_data.player_y, game_data->map_data.player_x, 0x000000, game_data->tile_size * 0.3, 0);
}

void	draw_player(t_cub3d *game_data)
{
	//draw_line(game_data, game_data->map_data.player_y, game_data->map_data.player_x, 200, game_data->player_angle);
	cast_fov_rays(game_data, 0x008000);
	//printf("draw_player x: %d\n", game_data->map_data.player_x);
	//printf("draw_player_y: %d\n", game_data->map_data.player_y);
	draw_square(game_data, game_data->map_data.player_y, game_data->map_data.player_x, 0xFF0000, game_data->tile_size * 0.3, 1);
}

void drawMap2D(int minimap_offset_y, t_cub3d *game_data)
{
	(void) minimap_offset_y;
	const int row = 15;
	const int col = 10;
	char map[15][10] =
	{
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
        {'1', '1', '1', '1', '1', '0', 'S', '1', '0', '1'},
        {'1', '1', '1', '1', '1', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '0', '0', '0', '0', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
        {'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
        {'1', '1', '0', '0', '0', '0', '0', '1', '1', '1'},
        {'1', '1', '1', '0', '1', '0', '1', '1', '1', '1'},
        {'1', '1', '1', '0', '1', '0', '1', '1', '1', '1'},
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
    };

	int	x;
	int	y;
	int	i;
	int	j;
	int square_size = calculateMinimapSquareSize(col, row, game_data);

	//printf("square_size: %d\n", square_size);
	x = 0;
	i = 0;
	j = 0;
	while (x < row * square_size)
	{
		y = 0;
		j = 0;
		while (y < col * square_size)
		{
			if (is_player_coord(x, y, game_data))
				draw_player(game_data);
			else if (map[i][j] == '1')
				draw_square(game_data, y, x, 0xFFFFFF, square_size, 1);
			y += square_size;
			j++;
		}
		x += square_size;
		i++;
	}
	//draw_square(game_data, 500, 500, 0x008000, 15);
	
}


void	get_player_coord(t_cub3d *game_data)
{
	const int row = 15;
	const int col = 10;
	char map[15][10] =
	{
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
        {'1', '1', '1', '1', '1', '0', 'S', '1', '0', '1'},
        {'1', '1', '1', '1', '1', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '0', '0', '0', '0', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
        {'1', '1', '1', '0', '0', '0', '1', '1', '1', '1'},
        {'1', '1', '0', '0', '0', '0', '0', '1', '1', '1'},
        {'1', '1', '1', '0', '1', '0', '1', '1', '1', '1'},
        {'1', '1', '1', '0', '1', '0', '1', '1', '1', '1'},
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
    };

	int	x;
	int	y;
	int	i;
	int	j;
	int square_size = calculateMinimapSquareSize(col, row, game_data);

	printf("square_size: %d\n", square_size);
	x = 0;
	i = 0;
	j = 0;
	while (x < row * square_size)
	{
		y = 0;
		j = 0;
		while (y < col * square_size)
		{
			if (map[i][j] == 'S')
			{
				game_data->map_data.player_x = x;
				game_data->map_data.player_y = y;
				break ;
			}
			y += square_size;
			j++;
		}
		x += square_size;
		i++;
	}
}

void move_up(t_cub3d *game_data, int distance)
{
	int		 x0 = game_data->map_data.player_x;
	int		 y0 = game_data->map_data.player_y;
	float	angle = game_data->player_angle;
	
	/* printf("x0: %d\n", x0);
	printf("y0: %d\n", y0);
	printf("angle: %f\n", angle); */

	int x1 = x0 + (float) distance * cos(angle); // Calculate the ending point (x-coordinate)
    int y1 = y0 + (float) distance * sin(angle); // Calculate the ending point (y-coordinate)

	/* printf("x1: %d\n", x1);
	printf("y1: %d\n", y1); */

	if (is_wall(x1, y1, 0, game_data))
		return ;
	erase_player(game_data);
	game_data->map_data.player_x = x1;
	game_data->map_data.player_y = y1;
	//printf("after x: %d\n", game_data->map_data.player_x);
	//printf("after y: %d\n", game_data->map_data.player_y);
	draw_player(game_data);
}

void move_down(t_cub3d *game_data, int distance)
{
	int		 x0 = game_data->map_data.player_x;
	int		 y0 = game_data->map_data.player_y;
	float	angle = game_data->player_angle;
	
	int x1 = x0 - (float) distance * cos(angle); // Calculate the ending point (x-coordinate)
	int y1 = y0 - (float) distance * sin(angle); // Calculate the ending point (y-coordinate)

	if (is_wall(x1, y1, 0, game_data))
		return ;
	erase_player(game_data);
	game_data->map_data.player_x = x1;
	game_data->map_data.player_y = y1;
	draw_player(game_data);
}

void	move_left(t_cub3d *game_data)
{
	erase_player(game_data);
	game_data->player_angle += degToRad(3);
	draw_player(game_data);
}

void	move_right(t_cub3d *game_data)
{
	erase_player(game_data);
	game_data->player_angle -= degToRad(3);
	draw_player(game_data);
}

int	key_down_hook(int keycode, t_cub3d *game_data)
{
	/* if (keycode == ESC)
	{
		destroy(game_data, "");
	} */
	if (keycode == 'w')
	{
		printf("key_down_hook\n");
		move_up(game_data, 10);
	}
	else if (keycode == 's')
		move_down(game_data, 10);
	else if (keycode == 'a')
		move_left(game_data);
	else if (keycode == 'd')
		move_right(game_data);
	return (0);
}

int	key_up_hook(int keycode, t_cub3d *game_data)
{
	printf("key_up_hook\n");
	(void) game_data;
	(void) keycode;
	return (0);
}

int	loop_hook(t_cub3d *game_data)
{
	drawMap2D(0 , game_data);
	//draw_player(game_data);
	return (0);
}

void	run_game(t_cub3d *game_data)
{
	// Draw the chessboard pattern on the window
    //draw_chessboard(game_data);
	game_data->player_angle = degToRad(46);
	get_player_coord(game_data);
	mlx_hook(game_data->mlx_win, KEY_PRESS_EVENT, KEY_PRESS_MASK,
		key_down_hook, game_data);
	mlx_hook(game_data->mlx_win, DESTROY_EVENT, KEY_PRESS_MASK,
		handle_closewindow, game_data);
	mlx_loop_hook(game_data->mlx, loop_hook, game_data);
	mlx_loop(game_data->mlx);
	return ;
}

/* int FixAng(int a)
{
	if (a > 359)
	{
		a -= 360;
	}
	if (a < 0)
	{
		a += 360;
	}
	return (a);
}

float px,py,pdx,pdy,pa;

void drawPlayer2D()
{
	glColor3f(1,1,0);
	glPointSize(8);
	glLineWidth(4);
	glBegin(GL_POINTS);
	glVertex2i(px,py);
	glEnd();
	glBegin(GL_LINES); 
	glVertex2i(px,py);
	glVertex2i(px+pdx*20,py+pdy*20);
	glEnd();
}
 */
/* void Buttons(unsigned char key,int x,int y)
{
 if(key=='a'){ pa+=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));} 	
 if(key=='d'){ pa-=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));} 
 if(key=='w'){ px+=pdx*5; py+=pdy*5;}
 if(key=='s'){ px-=pdx*5; py-=pdy*5;}
 glutPostRedisplay();
}//----------------------------------------------------------------------------- */


//---------------------------Draw Rays and Walls--------------------------------

/* void drawRays2D()
{
	glColor3f(0,1,1);
	glBegin(GL_QUADS);
	glVertex2i(526,  0);
	glVertex2i(1006,  0);
	glVertex2i(1006,160);
	glVertex2i(526,160);
	glEnd();	
	glColor3f(0,0,1);
	glBegin(GL_QUADS);
	glVertex2i(526,160);
	glVertex2i(1006,160);
	glVertex2i(1006,320);
	glVertex2i(526,320);
	glEnd();	 	
		
	int r,mx,my,mp,dof; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
	
	ra=FixAng(pa+30);                                                              //ray set back 30 degrees
	
	for(r=0;r<60;r++)
	{
		//---Vertical--- 
		dof=0; disV=100000;
		float Tan=tan(degToRad(ra));
			if(cos(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
		else if(cos(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
		else { rx=px; ry=py; dof=8;}                                                  //looking up or down. no hit  

		while(dof<8) 
		{ 
		mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
		if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
		else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
		} 
		vx=rx; vy=ry;

		//---Horizontal---
		dof=0; disH=100000;
		Tan=1.0/Tan; 
			if(sin(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;}//looking up 
		else if(sin(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;}//looking down
		else{ rx=px; ry=py; dof=8;}                                                   //looking straight left or right
		
		while(dof<8) 
		{ 
		mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
		if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
		else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
		} 

		glColor3f(0,0.8,0);
		if(disV<disH){ rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}                  //horizontal hit first
		glLineWidth(2); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();//draw 2D ray
			
		int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
		int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
		int lineOff = 160 - (lineH>>1);                                               //line offset
		
		glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineOff);glVertex2i(r*8+530,lineOff+lineH);glEnd();//draw vertical wall  

		ra=FixAng(ra-1);                                                              //go to next ray
	}
} */



/* void draw_chessboard(t_cub3d *game_data)
{
    int num_squares_x = 15;
    int num_squares_y = 15;

    int start_x = 0;
    int start_y = 0;
    printf("start x: %d\n", start_x);
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
} */


