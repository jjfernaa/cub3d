#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (validate_arguments(argc, argv) != 0) // Nueva funcion
		return (1);
	if (init_game(&game) != 0)
		// lo pongo aqui para evitar que ft_memset borre las texturas
		return (1);
	if (load_map(argv[1], &game) != 0)
		// nueva funcion que valida y carga el mapa
	{
		print_error("Error: Failed to read map\n");
		cleanup_game(&game);
	}
	if (init_graphics(&game) != 0)
	{
		cleanup_game(&game);
		return (1);
	}
	if (load_textures(&game) != 0)
	{
		print_error("Error: textures are not loading");
		cleanup_game(&game);
		return (1);
	}
	run_game(&game); // nueva funcion
	cleanup_game(&game);
	return (0);
}
