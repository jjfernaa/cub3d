#include "../../includes/cub3d.h"

// Necesito mejorar esta funcion para que detectr la colision con un margen
int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= game->map_height)// Necesito altura del mapa
		return (1);
	if (map_x < 0 || map_x >= game->map_width) // Necesito el ancho del mapa
		return (1);
	if (game->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	move_vertical(t_game *game, int direction)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = MOVE_SPEED * direction;
	new_x = game->player.x + game->player.dir_x * speed;
	new_y = game->player.y + game->player.dir_y * speed;
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	move_side(t_game *game, int direction)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = MOVE_SPEED * direction;
	new_x = game->player.x + game->player.plane_x * speed;
	new_y = game->player.y + game->player.plane_y * speed;
	if(!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	move_rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	// Guardo valores antiguos
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	// Rotar vector direccion
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	// Rotar plano de la camara
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}

void	mouse_callback(double xpos, double ypos, void *param)
{
	t_game	*game;
	double	x_off;

	//Ignorar el primer movimiento
	game = (t_game *)param;
	(void)ypos;
	if (game->player.first_mouse)
	{
		game->player.mouse_x = xpos;
		game->player.first_mouse = 0;
		return ;
	}
	// Calcular desplazamiento
	x_off = xpos - game->player.mouse_x;
	game->player.mouse_x = xpos;
	// Sensibilidad del raton
	x_off *= MOUSE_SENSITIVITY;
	move_rotate(game, x_off);
}


