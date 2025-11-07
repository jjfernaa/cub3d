#include "../../includes/cub3d.h"

uint32_t	create_color(int r, int g, int b)
{
	return(r << 24 | g << 16 | b << 8 | 0xFF);
}
void	render_background(t_game *game)
{
	int			x;
	int			y;
	uint32_t	ceiling;
	uint32_t	floor;

	ceiling = create_color(133, 0, 0);
	floor = create_color(0, 0, 0);

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			if (y < W_HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, ceiling);
			else
				mlx_put_pixel(game->img, x, y, floor);
			x++;
		}
		y++;
	}
}