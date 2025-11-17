#include "../../includes/cub3d.h"

// Funcion ppara imprimir suelo del minimapa

void	d_tile(t_game *game, int x, int y, uint32_t color)
{
	int	px;
	int	py;

	py = 0;
	while (py < TILE_SIZE)
	{
		px = 0;
		while (px < TILE_SIZE)
		{
			if (x * TILE_SIZE + px < W_WIDTH && y * TILE_SIZE + py < W_HEIGHT)
			mlx_put_pixel(game->img, x * TILE_SIZE + px,
				y * TILE_SIZE + py, color);
			px++;
		}
		py++;
	}
}

void	d_minimap(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height && y * TILE_SIZE < W_HEIGHT)
	{
		x = 0;
		while (game->map[y][x] && x * TILE_SIZE < W_WIDTH)
		{
			if (game->map[y][x] == '1')
				d_tile(game, x, y, 0x000000FF); // Negro (pared)
			else if (game->map[y][x] == '0')
				d_tile(game, x, y, 0xFFFFFFFF); // Blanco (espacio)
			x++;
		}
		y++;
	}
}
void	d_player(t_game *game)
{
	int	px;
	int	py;
	int	player_size;
	int	screen_x;
	int	screen_y;

	player_size = TILE_SIZE / 2;
	py = -player_size;
	while (py < player_size)
	{
		px = -player_size;
		while (px < player_size)
		{
			screen_x = (int)(game->player.x * TILE_SIZE) + px;
			screen_y = (int)(game->player.y * TILE_SIZE) + py;
			if (screen_x >= 0 && screen_x < W_WIDTH &&
				screen_y >= 0 && screen_y < W_HEIGHT)
			mlx_put_pixel(game->img, screen_x, screen_y, 0xFF0000FF); // Rojo 
			px++;
		}
		py++;
	}
}
