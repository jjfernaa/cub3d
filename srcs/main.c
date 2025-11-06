#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;
	
	ft_memset(&game, 0, sizeof(t_game));
	
	if (argc != 2)
	{
		print_error("Error: Invalid arguments\n");
		return(-1);
	}
	return (0);
}