#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argv;
	if (argc != 2)
	{
		print_error("Error: Invalid arguments\n");
		return(-1);
	}
	if (init_game(&game) != 0)
		return (1);
	if (init_window(&game) != 0)
		return (1);
	if (init_textures(&game) != 0)
		return (1);
	if (init_player(&game) != 0)
		return (1);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}