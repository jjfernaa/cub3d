#include "../../includes/cub3d.h"

static int	in_bounds(int x, int y)
{
	return (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT);
}
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
				mlx_put_pixel(game->img, x * TILE_SIZE + px, y * TILE_SIZE + py,
					color);
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
			else if (game->map[y][x] == ' ')
				d_tile(game, x, y, 0x808080FF); // Gris (espacio vacío)
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
	int	center_x;
	int	center_y;

	player_size = TILE_SIZE / 3;
	center_x = (int)(game->player.x * TILE_SIZE);
	center_y = (int)(game->player.y * TILE_SIZE);
	py = -player_size;
	while (py <= player_size)
	{
		px = -player_size;
		while (px <= player_size)
		{
			if (px * px + py * py <= player_size * player_size)
			{
				if (in_bounds(center_x + px, center_y + py))
					mlx_put_pixel(game->img, center_x + px, center_y + py,
						COL_P);
			}
			px++;
		}
		py++;
	}
}
void	d_direction(t_game *game)
{
	int	i;
	int	start_x;
	int	start_y;
	int	line_length;

	start_x = (int)(game->player.x * TILE_SIZE);
	start_y = (int)(game->player.y * TILE_SIZE);
	line_length = TILE_SIZE * 2;
	i = 0;
	while (i < line_length)
	{
		if (in_bounds(start_x + (int)(game->player.dir_x * i), start_y
				+ (int)(game->player.dir_y * i)))
			mlx_put_pixel(game->img, start_x + (int)(game->player.dir_x * i),
				start_y + (int)(game->player.dir_y * i), 0xFFFF00FF);
		i++;
	}
}
