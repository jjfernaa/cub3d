#include "../../includes/cub3d.h"

int	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	return (0);
}

int	init_window(t_game *game)
{
	game->mlx = mlx_init(W_WIDTH, W_HEIGHT, "cub3D", true);
	if (!game->mlx)
		return (print_error("Error: Failed to initialize MLX\n"));
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	if (!game->img)
	{
		mlx_terminate(game->mlx);
		return (print_error("Error: Failed to create image\n"));
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		mlx_delete_image(game->mlx, game->img);
		mlx_terminate(game->mlx);
		return (print_error("Error: Failed to display image\n"));
	}
	return (0);
}

int	init_textures(t_game *game)
{
	(void)game;
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.east = NULL;
	game->textures.west = NULL;
	return (0);
}

int	init_player(t_game *game)
{
	if (player_position(game) != 0)
		return (print_error("Error : Player not found in map\n"));
	game->player.mouse_x = W_WIDTH / 2.0;
	game->player.first_mouse = 1;
	return (0);
}
// cree esta funcion para descomprimir el main

int	init_graphics(t_game *game)
{
	if (init_window(game) != 0)
		return (-1);
	if (init_textures(game) != 0)
	{
		clean_mlx(game);
		return (-1);
	}
	if (init_player(game) != 0)
	{
		clean_mlx(game);
		return (-1);
	}
	return (0);
}
