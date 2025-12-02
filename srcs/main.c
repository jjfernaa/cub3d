#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (validate_arguments(argc, argv) != 0)
		return (1);
	if (init_game(&game) != 0)
		return (1);
	if (load_map(argv[1], &game) != 0)
	{
		cleanup_game(&game);
		return (1);
	}
	if (load_textures(&game) != 0)
	{
		cleanup_game(&game);
		return (1);
	}
	if (init_graphics(&game) != 0)
	{
		cleanup_game(&game);
		return (1);
	}
	run_game(&game);
	cleanup_game(&game);
	return (0);
}
