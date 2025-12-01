/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:26:19 by lginer-m          #+#    #+#             */
/*   Updated: 2025/12/01 00:21:16 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

void	clean_mlx(t_game *game)
{
	if (game->mlx)
	{
		if (game->img)
		{
			mlx_delete_image(game->mlx, game->img);
			game->img = NULL;
		}
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	free_textures(game);
	free_map(game);
	clean_mlx(game);
}

void	path_to_null(t_game *game)
{
	game->textures.north_path = NULL;
	game->textures.south_path = NULL;
	game->textures.east_path = NULL;
	game->textures.west_path = NULL;
	game->textures.floor = NULL;
	game->textures.ceiling = NULL;
}

int	check_split_rgb(char **split)
{
	if (!split || !split[0] || !split[1] || !split[2])
	{
		free_split(split);
		return (1);
	}
	return (0);
}
