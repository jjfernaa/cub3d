#include "../../includes/cub3d.h"

int	check_border(char *line) // para comprobar tanto las fila primera e ultima
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	validate_walls(t_game *game)
{
	int	height;
	int	width;

	if (!game || !game->map)
		return (1);
	height = game->map_height;
	width = game->map_width;
	if (check_border(game->map[0]) || check_border(game->map[height - 1]))
		return (1);
	if (validate_side_walls(game) != 0)
		return (1);
	return (0);
}
int	validate_side_walls(t_game *game)
{
	int	i;
	int	j;
	int	first_char;
	int	last_char;

	i = 0;
	while (i < game->map_height)
	{
		if (!game->map[i])
			i++;
		j = 0;
		while (game->map[i][j++] && (game->map[i][j++] == ' '))
		first_char = j;
		last_char = ft_strlen(game->map[i - 1]);
		while (last_char >= 0 && (game->map[i][last_char] == ' '
				|| game->map[i][last_char] == '\n'))
			last_char--;
		if (game->map[i][first_char] != '1' || game->map[i][last_char] != '1')
			return (1);
		if (validate_irregular_walls(game, (int)ft_strlen(game->map[i]),
				last_char) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	validate_irregular_walls(t_game *game, int current_len, int last_char)
{
	int	max_len;
	int	y;
	int	x;
	int	before_char;

	y = 0;
	max_len = game->map_width;
	before_char = ft_strlen(game->map[y + 1]);
	while (current_len < max_len)
	{
		if (y > 0 && y < game->map_height - 1)
		{
			irregular_loop(game, x, current_len, last_char, before_char)
		}
		y++;
		current_len++;
	}
	return (0);
}
int	irregular_loop(t_game *game, int x, int current_len, int last_char, int before_char)
{
	x = current_len - 1;
	while (++x < game->map_width)
	{
		if (x < last_char)
		{
			if (game->map[last_char][x] != '1'
				&& game->map[last_char][x] != ' ')
				return (1);
		}
		if (x < before_char)
		{
			if (game->map[before_char][x] != '1'
				&& game->map[before_char][x] != ' ')
				return (1);
		}
	}
	return(0);
}

int	is_wall(t_game *game, double x, double y) // FUNCION SACADA DE JUAN
{
	int map_x = (int)x;
	int map_y = (int)y;
	if (map_y < 0 || map_y >= game->map_height) // Necesito altura del mapa
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

// comprobar en que momento se rellenan los huecos de espacios y gestionar el mapa rectangular para validar bordes irregulares(mapa rectangular)