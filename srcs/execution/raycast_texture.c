#include "../../includes/cub3d.h"

void	calculate_wall_x(t_game *game, t_ray *ray)
{
	if (ray->side == 0) // Pared vertical (E/W)
		ray->wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else // Paref horizontal (N/S)
		ray->wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x); // Parete decimal(0.0 - 1.0)
}

void	select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0) // pared vertical (E/W)
	{
		if (ray->ray_dir_x > 0)
			ray->texture = game->textures.east;
		else
			ray->texture = game->textures.west;
	}
	else // pared horizontal (N/S)
	{
		if (ray->ray_dir_y > 0)
			ray->texture = game->textures.south;
		else
			ray->texture = game->textures.north;
	}
}

void	calculate_tex_x(t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * (double)ray->texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) // invierte textura en ciertos lados para que quede bien
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
}

uint32_t	get_texture_color(mlx_texture_t *texture, int x, int y)
{
	uint8_t		*pixel;
	int			index;

	index = (y * texture->width + x) * 4;
	pixel = &texture->pixels[index];
	return ((pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]);
}
