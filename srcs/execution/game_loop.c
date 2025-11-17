#include "../../includes/cub3d.h"
// Nueva fucnion para cerra ventana
static void	close_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_close_window(game->mlx);
}
// Funcion para ejecutar el juego constantemente, configuro tecla ESC por ahora,
void	updates_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_input(game);
	render_background(game);// Agrego render del fondo en la actualizacion del juego
	d_minimap(game);
	d_player(game);
    //draw_direction(t_game *game);
	// implementar update_player
	// implementar render_frame
}

void	run_game(t_game *game)
{
	mlx_cursor_hook(game->mlx, &mouse_callback, game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(game->mlx, &updates_game, game);
	mlx_close_hook(game->mlx, &close_hook, game); // implemente close_hook(void *param)
	mlx_loop(game->mlx);
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
	// Flechas del teclado
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		move_rotate(game, -ROT_SPEED);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		move_rotate(game, ROT_SPEED);
	// Salir
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
