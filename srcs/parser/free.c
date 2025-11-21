#include "../../includes/cub3d.h"

void	free_mlx_textures(t_game *game)
{
	printf("Debug: north=%p, south=%p, west=%p, east=%p\n", 
    game->textures.north, game->textures.south, 
	game->textures.west, game->textures.east);
	if (game->textures.north)
	{
		mlx_delete_texture(game->textures.north);
		game->textures.north = NULL;
	}
	if (game->textures.south)
	{
		mlx_delete_texture(game->textures.south);
		game->textures.south = NULL;
	}
	if (game->textures.east)
	{
		mlx_delete_texture(game->textures.east);
		game->textures.east = NULL;
	}
	if (game->textures.west)
	{
		mlx_delete_texture(game->textures.west);
		game->textures.west = NULL;
	}
	printf("✅ free_mlx_textures\n"); 
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
	printf("✅ free_path_textures\n"); 
}


void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map == NULL)
		return ;
	while (game->map && game->map[i])
		free(game->map[i++]);
	free(game->map);
	game->map = NULL;
	printf("✅ free_map\n"); 
}

void	free_split(char **str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
			free(str[i++]);
		free(str);
	}
	printf("✅ free_split\n"); 
}
