#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argv;
	if (argc != 2)
	{
		print_error("Error: Invalid arguments\n");
		return (1);
	}
	if(check_extension(argv[1]) != 1)
		print_error("Error: Invalid map extension\n");
	if(count_lines(argv[1]) != 1)
		print_error("Error: Failed to read map\n");
	printf("mapa: %d\n", count_lines(argv[1]));
		return(-1);
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