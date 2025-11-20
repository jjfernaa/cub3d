#include "../../includes/cub3d.h"

void	set_direction(t_game *game, double x, double y)
{
	game->player.dir_x = x;
	game->player.dir_y = y;
}

void	set_plane(t_game *game, double x, double y)
{
	game->player.plane_x = x;
	game->player.plane_y = y;
}
