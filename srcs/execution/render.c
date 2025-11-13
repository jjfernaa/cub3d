#include "../../includes/cub3d.h"

void	render_background(t_game *game)
{
	int			x;
	int			y;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			if (y < W_HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, game->ceiling_color);
			else
				mlx_put_pixel(game->img, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}
