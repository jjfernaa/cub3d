#include "../../includes/cub3d.h"

int	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	return (0);
}

int	init_window(t_game *game)
{
	game->mlx = mlx_init(W_WIDTH, W_HEIGHT, "cub3D", true);
	if (!game->mlx)
	{
		print_error("Error: Failed to initialize MLX\n");
		return (-1);
	}
	game->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	if (!game->img)
	{
		print_error("Error: Failed to create image\n");
		mlx_terminate(game->mlx);
		return (-1);
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		print_error("Error: Failed to display image\n");
		mlx_terminate(game->mlx);
		return (-1);
	}
	return (0);
}

int	init_textures(t_game *game)
{
	(void)game;
	return (0);
}

int	init_player(t_game *game)
{
	game->player.x = 5.0;
	game->player.y = 5.0;	
	game->player.dir_x = -1.0;
	game->player.dir_y = 0.0;	
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
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
	render_background(game);
	return (0);
}