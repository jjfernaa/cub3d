#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	(void)argv;
	t_game	*game;

	if (argc != 2)
	{
		print_error("Error\n");
		return(-1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	return (0);

}