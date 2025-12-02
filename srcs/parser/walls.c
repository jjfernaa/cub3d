#include "../../includes/cub3d.h"

int	check_border(char *line)
{
	int	i;

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

	if (!game || !game->map)
		return (1);
	height = game->map_height;
	if (check_border(game->map[0]) || check_border(game->map[height - 1]))
		return (1);
	if (validate_side_walls(game) != 0)
		return (1);
	if (validate_irregular(game) != 0)
		return (1);
	return (0);
}

int	validate_side_walls(t_game *game)
{
	int	i;
	int	j;
	int	last_char;

	i = 0;
	while (i < game->map_height)
	{
		if (!game->map[i])
		{
			i++;
			continue ;
		}
		j = 0;
		while (game->map[i][j] && (game->map[i][j] == ' '))
			j++;
		last_char = ft_strlen(game->map[i]) - 1;
		while (last_char >= 0 && (game->map[i][last_char] == ' '
			|| game->map[i][last_char] == '\n'))
			last_char--;
		if (game->map[i][j] != '1' || game->map[i][last_char] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= game->map_height)
		return (1);
	if (map_x < 0 || map_x >= game->map_width)
		return (1);
	if (!game->map[map_y])
		return (1);
	if (game->map[map_y][map_x] == '\0' || game->map[map_y][map_x] == '\n'
		|| game->map[map_y][map_x] == ' ')
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
