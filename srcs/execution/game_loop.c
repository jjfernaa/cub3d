#include "../../includes/cub3d.h"

// Funcion para ejecutar el juego constantemente, configuro tecla ESC por ahora,
void	updates_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_input(game);
	// implementar handle_input
	// implementar update_player
	// implementar render_frame
}
void	run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, &updates_game, game);
	//mlx_close_hook(game->mlx, &close_hook, game);// implemetar close_hook(void *param)
	mlx_loop(game->mlx);
}