#include "../../includes/cub3d.h"

void	move_vertical(t_game *game, int direction)
{
	double	new_x;
	double	new_y;
	double	speed;
	
	speed = MOVE_SPEED * direction;
	new_x = game->player.x + game->player.plane_x * speed;
	new_y = game->player.y + game->player.plane_y * speed;
}

void	move_side(t_game *game, int direction)
{
	double	new_x;
	double	new_y;
	double	speed;

	speed = MOVE_SPEED * direction;
	new_x = game->player.x + game->player.plane_x * speed;
	new_y = game->player.y + game->player.plane_y * speed;

}

void	move_rotate(t_game *game, double angle)
{

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
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
