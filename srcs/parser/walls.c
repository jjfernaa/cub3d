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
int	is_wall(t_game *game, double x, double y) //FUNCION SACADA DE JUAN
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= game->map_height)// Necesito altura del mapa
		return (1);
	if (map_x < 0 || map_x >= game->map_width) // Necesito el ancho del mapa
		return (1);
	if (!game->map[map_y]) // Verifica que fila existe
		return (1);
	if (map_x >= (int)ft_strlen(game->map[map_y])) // Verifica columna
		return (1);
	if (game->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	check_collision(t_game *game, double x, double y)
{
	if (is_wall(game, x, y))
		return (1);
	if (is_wall(game, x + COLLISION_MARGEN, y))
		return (1);
	if (is_wall(game, x - COLLISION_MARGEN, y))
		return (1);
	if (is_wall(game, x, y + COLLISION_MARGEN))
		return (1);
	if (is_wall(game, x, y - COLLISION_MARGEN))
		return (1);
	return (0);
}
