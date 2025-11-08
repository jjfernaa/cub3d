#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game game;

	int line_count;

	if (argc != 2)
		print_error("Error: Invalid arguments\n");
	if (check_extension(argv[1]) != 1)
		print_error("Error: Invalid map extension\n");
	if (init_game(&game) != 0) //lo pongo aqui para evitar que ft_memset borre las texturas
		return (1);
	line_count = count_lines(argv[1], &game);
	if (line_count <= 0)
		print_error("Error: Failed to read map\n");
	if (init_window(&game) != 0)
		return (1);
	if (init_textures(&game) != 0)
		return (1);
	if (init_player(&game) != 0)
		return (1);
	render_background(&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}