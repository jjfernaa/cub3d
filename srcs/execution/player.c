#include "../../includes/cub3d.h"

void	move_vertical(t_game *game, int direction)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = MOVE_SPEED * direction;
	new_x = game->player.x + game->player.dir_x * speed;
	new_y = game->player.y + game->player.dir_y * speed;
	game->player.x = new_x;
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
	game->player.x = new_x;
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

void	handle_input(t_game *game)
{
	// Movimientos adelante y atras
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_vertical(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_vertical(game, -1);
	// Movimientos laterales
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_side(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_side(game, 1);
	// Salir
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
