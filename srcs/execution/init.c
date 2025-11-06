#include "../../includes/cub3d.h"

int	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->w_width = 1280;
	game->w_height = 720;
	return (0);
}

int	init_window(t_game *game)
{
	game->mlx = mlx_init(game->w_width, game->w_height, "cub3D", true);
	if (!game->mlx)
	{
		print_error("Error: Failed to initialize MLX\n");
		return (-1);
	}
	game->img = mlx_new_image(game->mlx, game->w_width, game->w_height);
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


