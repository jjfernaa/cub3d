#include "../../includes/cub3d.h"

void	free_mlx_textures(t_game *game)
{
	if (game->textures.north)
		mlx_delete_texture(game->textures.north);
	if (game->textures.south)
		mlx_delete_texture(game->textures.south);
	if (game->textures.east)
		mlx_delete_texture(game->textures.east);
	if (game->textures.west)
		mlx_delete_texture(game->textures.west);
}
void	free_path_textures(t_game *game)
{
	if (game->textures.north_path)
		free(game->textures.north_path);
	if (game->textures.south_path)
		free(game->textures.south_path);
	if (game->textures.east_path)
		free(game->textures.east_path);
	if (game->textures.west_path)
		free(game->textures.west_path);
	if (game->textures.floor)
		free(game->textures.floor);
	if (game->textures.ceiling)
		free(game->textures.ceiling);
	path_to_null(game);
}
