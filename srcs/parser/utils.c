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
	(void)game;
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
// se podría liberar memoria o parte del mapa en esta funcion

// Tendriamos que implementar free_textures(t_game *game), free_map(t_game *game)