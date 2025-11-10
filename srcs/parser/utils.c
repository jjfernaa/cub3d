#include "../../includes/cub3d.h"

void	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
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
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
}
void	free_textures(t_game *game)
{
	free_mlx_textures(game);
	free_path_textures(game);
}

void	free_map(t_game *game)
{
	(void)game;
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
// se podría liberar memoria o parte del mapa en esta funcion

// Tendriamos que implementar free_textures(t_game *game), free_map(t_game *game)