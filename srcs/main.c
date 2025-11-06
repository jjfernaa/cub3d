#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	//t_game	*game;

	if(argc != 2)
		print_error("Error: Invalid arguments\n");
	//ft_memset(&game, 0, sizeof(t_game));
	if(check_extension(argv[1]) != 1)
		print_error("Error: Invalid map extension\n");
	if(count_lines(argv[1]) != 1)
		print_error("Error: Failed to read map\n");
	printf("mapa: %d\n", count_lines(argv[1]));
	return (0);
}