#include "../../includes/cub3d.h"

static void	init_draw_params(t_ray *ray, t_draw *draw)
{
	// Altura del la linea a dibujar
	draw->line_height = (int)(W_HEIGHT / ray->perp_wall_dist);

	// calcular inicio y fin del diibujo
	draw->draw_start = -draw->line_height / 2 + W_HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + W_HEIGHT / 2;
	if (draw->draw_end >= W_HEIGHT)
		draw->draw_end = W_HEIGHT - 1;
	// paso para recorrer la textura verticalmente
	draw->step = 1.0 * ray->texture->height / draw->line_height;
	// Posicione inicial el la textura
	draw->tex_pos = (draw->draw_start - W_HEIGHT / 2 + draw->line_height / 2)
		* draw->step;
}

// Dibuja una columna vertical con textura
void	draw_texture_wall(t_game *game, t_ray *ray, int x)
{
	t_draw		draw;
	int			y;
	uint32_t	color;

	init_draw_params(ray, &draw);
	y = 0;
	while (y < draw.draw_start) // Pintar techo 
	{
		mlx_put_pixel(game->img, x, y, game->ceiling_color);
		y++;
	}
	y = draw.draw_start;
	while (y < draw.draw_end) // dibuja cada pixel en la textura
	{
		ray->tex_y = (int)draw.tex_pos & (ray->texture->height - 1);
		draw.tex_pos += draw.step;
		color = get_texture_color(ray->texture, ray->tex_x, ray->tex_y);
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
	while (y < W_HEIGHT)
	{
		mlx_put_pixel(game->img, x, y, game->floor_color);
		y++;
	}
}
