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
		mlx_terminate(game->mlx);
		game->mlx = NULL;
		printf("✅ Clean_mlx\n"); 
	}
}

void	free_textures(t_game *game)
{
	free_mlx_textures(game);
	free_path_textures(game);
	printf("✅ Clean_all_textures\n"); 
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	printf("🧹 Cleaning up game...\n");  // ← Debug temporal
	free_textures(game);
	free_map(game);
	clean_mlx(game);
	printf("✅ Cleanup completed\n");    // ← Debug temporal
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

