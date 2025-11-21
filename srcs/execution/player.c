#include "../../includes/cub3d.h"

int	init_player(t_game *game)
{
	if (player_position(game) != 0)
		return (print_error("Error : Player not found in map\n"));
	game->player.mouse_x = W_WIDTH / 2.0;
	game->player.first_mouse = 1;
	return (0);
}

// Funcion para detectar la posicion del jugaror
// Recorre el mapa buscando N,S,E,W , Cuando lo encuentra, coloca al jugador en el centro de la celda
// Llama a la funcion player_direction() para cinfigurar hacia donde mira.
int	player_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				game->player.x = x + 0.5; // ubica al jugador en el centro de la celda
				game->player.y = y + 0.5;
				player_direction(game, game->map[y][x]); // esta funcion setea la direccion
				game->map[y][x] = '0';// convertit a 0 una vez encontrado para evitar errores
				return (0);// Si lo encuentra
			}
			x++;
		}
		y++;
	}
	return (1); // salimos con uno en caso de no encontrar al jugador!
}

/* Funcion para setear la direccion del jugador, funciona con dos funciones auxiliares que estan en utils_player que ayudan a setear la direccion y el plano del mismo para reducir el tamaño de esta 
funcion */
void	player_direction(t_game *game, char direction)
{
	if (direction == 'N')
	{
		set_direction(game, 0.0, -1.0);
		set_plane(game, 0.66, 0.0);
	}
	else if (direction == 'S')
	{
		set_direction(game, 0.0, 1.0);
		set_plane(game, -0.66, 0.0);
	}
	else if (direction == 'E')
	{
		set_direction(game, 1.0, 0.0);
		set_plane(game, 0.0, 0.66);
	}
	else if (direction == 'W')
	{
		set_direction(game, -1.0, 0.0);
		set_plane(game, 0.0, -0.66);
	}
}

