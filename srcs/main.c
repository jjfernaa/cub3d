#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	int 	line_count;

	if (validate_arguments(argc, argv) != 0) // Nueva funcion
		return (1);
	if (init_game(&game) != 0) //lo pongo aqui para evitar que ft_memset borre las texturas
		return (1);
	line_count = count_lines(argv[1], &game);
	if (line_count <= 0)
	{
		print_error("Error: Failed to read map\n");
		cleanup_game(&game);
		return (1);
	}
	if (init_graphics(&game) != 0) // nueva funcion
	{
		cleanup_game(&game);
		return (1);
	}
	run_game(&game);   // nueva funcion
	cleanup_game(&game);
	return (0);
}
