#include "../../includes/cub3d.h"

int	check_border(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n'
			&& line[i] != '\t')
			return (1); 
		i++;
	}
	return(0); 
}

int	validate_map_border(t_game *game)
{
	int	i;
	int	height;
	int	width;

	if (!game || !game->map)
		return (1);
	i = 0;
	height = game->map_height;
	width = game->map_width;
	if (check_border(game->map[0]) || check_border(game->map[height
			- 1])) 
		return (print_error("Error: Border row must be surronded by walls\n"));
	if (game->map[0][0] != '1' || game->map[0][width - 1] != '1')
		return (print_error("Error: First row must start and end with walls\n"));
	if (game->map[height - 1][0] != '1' || game->map[height - 1][width
		- 1] != '1') //verificar columnas laterales
		return (print_error("Error: Last row must start and end with walls\n"));
	while (i < height)
	{
		if (game->map[i][0] != '1' || game->map[i][width - 1] != '1')
			return (print_error("Error: Side columns must be walls\n"));
		i++;
	}
	return (0);
}
