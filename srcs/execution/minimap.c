/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 20:14:14 by juan-jof          #+#    #+#             */
/*   Updated: 2025/12/03 20:14:15 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	in_bounds(int x, int y)
{
	return (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT);
}

void	d_tile(t_game *game, int screen_x, int screen_y, uint32_t color)
{
	int	px;
	int	py;

	py = 0;
	while (py < TILE_SIZE)
	{
		px = 0;
		while (px < TILE_SIZE)
		{
			if (in_bounds(screen_x + px, screen_y + py))
				mlx_put_pixel(game->img, screen_x + px, screen_y + py, color);
			px++;
		}
		py++;
	}
}

void	d_minimap(t_game *game)
{
	int	map_y;
	int	screen_y;
	int	row;

	screen_y = game->mini_s_y;
	row = 0;
	while (row < MINIMAP_RADIUS * 2 + 1)
	{
		map_y = (int)game->player.y - MINIMAP_RADIUS + row;
		draw_minimap_row(game, map_y, &screen_y);
		screen_y += TILE_SIZE;
		row++;
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
	center_x = MINI_S_X + (MINIMAP_RADIUS * TILE_SIZE) + (TILE_SIZE / 2);
	center_y = game->mini_s_y + (MINIMAP_RADIUS * TILE_SIZE) + (TILE_SIZE / 2);
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

	start_x = MINI_S_X + (MINIMAP_RADIUS * TILE_SIZE) + (TILE_SIZE / 2);
	start_y = game->mini_s_y + (MINIMAP_RADIUS * TILE_SIZE) + (TILE_SIZE / 2);
	i = 0;
	while (i < TILE_SIZE * 2)
	{
		if (in_bounds(start_x + (int)(game->player.dir_x * i), start_y
			+ (int)(game->player.dir_y * i)))
			mlx_put_pixel(game->img, start_x + (int)(game->player.dir_x * i),
				start_y + (int)(game->player.dir_y * i), 0x0000FFFF);
		i++;
	}
}
