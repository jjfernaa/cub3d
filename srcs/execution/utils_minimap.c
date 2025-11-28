#include "../../includes/cub3d.h"

uint32_t	get_tile_color(char c)
{
	if (c == '1')
		return (0x000000FF);
	else if (c == '0')
		return (0xFFFFFFFF);
	else
		return (0x808080FF);
}
int	is_valid_map_pos(t_game *game, int map_x, int map_y)
{
	if (map_y < 0 || map_y >= game->map_height)
		return (0);
	if (map_x < 0 || map_x >= (int)ft_strlen(game->map[map_y]))
		return (0);
	return (1);
}
void	draw_minimap_row(t_game *game, int map_y, int *screen_y)
{
	int			map_x;
	int			screen_x;
	uint32_t	color;
	int			col;

	screen_x = MINIM_OFFSET_X;
	col = 0;
	while (col < MINIMAP_RADIUS * 2 + 1)
	{
		map_x = (int)game->player.x - MINIMAP_RADIUS + col;
		if (is_valid_map_pos(game, map_x, map_y))
			color = get_tile_color(game->map[map_y][map_x]);
		else
			color = 0x808080FF; 
		d_tile(game, screen_x, *screen_y, color);
		screen_x += TILE_SIZE;
		col++;
	}
}
void	draw_minimap_border(t_game *game)
{
	int	i;
	int	size;
    int	offset_x;
    int	offset_y;

    size = (MINIMAP_RADIUS * 2 + 1) * TILE_SIZE;
    offset_x = MINIM_OFFSET_X;
    offset_y = MINIM_OFFSET_Y;
    i = 0;
    while (i <= size)
    {
        mlx_put_pixel(game->img, offset_x + i, offset_y, 0xFFFFFFFF);
        mlx_put_pixel(game->img, offset_x + i, offset_y + size, 0xFFFFFFFF);
        mlx_put_pixel(game->img, offset_x, offset_y + i, 0xFFFFFFFF);
        mlx_put_pixel(game->img, offset_x + size, offset_y + i, 0xFFFFFFFF);
        i++;
    }
}
