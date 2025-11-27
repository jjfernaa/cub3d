#include "../../includes/cub3d.h"
// Nueva fucnion para cerra ventana
static void	close_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_close_window(game->mlx);
}

static void	key_callback(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE) // cierra la ventana con ESC
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_SPACE) // muestra el mapa SPACE
		game->show_minimap = !game->show_minimap;
	if (keydata.key == MLX_KEY_TAB) // bloquea raton
	{
		game->mouse_locked = !game->mouse_locked;
		if (game->mouse_locked)
		{
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
			mlx_set_mouse_pos(game->mlx, W_WIDTH / 2, W_HEIGHT / 2);
			game->player.first_mouse = 1;
		}
		else
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	}
}

// Funcion para ejecutar el juego constantemente, configuro tecla ESC por ahora,
void	updates_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_input(game);
	cast_rays(game);
	if (game->show_minimap)
	{
		d_minimap(game);
		draw_minimap_border(game);
		d_player(game);
		d_direction(game);
	}
}

void	run_game(t_game *game)
{
	game->show_minimap = 0;
	game->mouse_locked = 1;
	mlx_cursor_hook(game->mlx, &mouse_callback, game);
	mlx_key_hook(game->mlx, &key_callback, game); //Agrego funucion manejo teclas
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(game->mlx, &updates_game, game);
	mlx_close_hook(game->mlx, &close_hook, game);
	mlx_loop(game->mlx);
}

void	handle_input(t_game *game)
{
	// Movimientos adelante y atras
	if (mlx_is_key_down(game->mlx, MLX_KEY_W)
		&& mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
		move_vertical(game, 3);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W))
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
}
