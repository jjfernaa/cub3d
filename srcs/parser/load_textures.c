/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 20:15:24 by lginer-m          #+#    #+#             */
/*   Updated: 2025/12/06 20:30:29 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	load_north_south(t_game *game)
{
	game->textures.north = mlx_load_png(game->textures.north_path);
	if (!game->textures.north)
		return (print_error("Error: Textures are not found\n"));
	game->textures.south = mlx_load_png(game->textures.south_path);
	if (!game->textures.south)
	{
		free_mlx_textures(game);
		return (print_error("Error: Textures are not found\n"));
	}
	return (0);
}

static int	load_east_west(t_game *game)
{
	game->textures.east = mlx_load_png(game->textures.east_path);
	if (!game->textures.east)
	{
		free_mlx_textures(game);
		return (print_error("Error: Textures are not found\n"));
	}
	game->textures.west = mlx_load_png(game->textures.west_path);
	if (!game->textures.west)
	{
		free_mlx_textures(game);
		return (print_error("Error: Textures are not found\n"));
	}
	return (0);
}

int	load_textures(t_game *game)
{
	if (check_paths(game) != 0)
		return (1);
	if (load_north_south(game) != 0)
		return (1);
	if (load_east_west(game) != 0)
		return (1);
	if (!game->ceiling_color || !game->floor_color)
		return (print_error("Error: Background not found\n"));
	return (0);
}

int	check_paths(t_game *game)
{
	if (!game->textures.north_path)
		return (print_error("Error: Missing north texture path\n"));
	if (!game->textures.south_path)
		return (print_error("Error: Missing south texture path\n"));
	if (!game->textures.east_path)
		return (print_error("Error: Missing east texture path\n"));
	if (!game->textures.west_path)
		return (print_error("Error: Missing west texture path\n"));
	return (0);
}
