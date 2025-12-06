/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 20:14:26 by juan-jof          #+#    #+#             */
/*   Updated: 2025/12/06 19:58:19 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_player(t_game *game)
{
	game->player.mouse_x = W_WIDTH / 2.0;
	game->player.first_mouse = 1;
	return (0);
}

int	player_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				player_direction(game, game->map[y][x]);
				game->map[y][x] = '0';
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

void	player_direction(t_game *game, char direction)
{
	if (direction == 'N')
	{
		set_direction(game, 0.0, -1.0);
		set_plane(game, 0.66, 0.0);
	}
	else if (direction == 'S')
	{
		set_direction(game, 0.0, 1.0);
		set_plane(game, -0.66, 0.0);
	}
	else if (direction == 'E')
	{
		set_direction(game, 1.0, 0.0);
		set_plane(game, 0.0, 0.66);
	}
	else if (direction == 'W')
	{
		set_direction(game, -1.0, 0.0);
		set_plane(game, 0.0, -0.66);
	}
}

void	set_direction(t_game *game, double x, double y)
{
	game->player.dir_x = x;
	game->player.dir_y = y;
}

void	set_plane(t_game *game, double x, double y)
{
	game->player.plane_x = x;
	game->player.plane_y = y;
}
