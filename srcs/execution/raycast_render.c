/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 20:14:30 by juan-jof          #+#    #+#             */
/*   Updated: 2025/12/03 20:14:31 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_draw_params(t_ray *ray, t_draw *draw)
{
	draw->line_height = (int)(W_HEIGHT / ray->perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + W_HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + W_HEIGHT / 2;
	if (draw->draw_end >= W_HEIGHT)
		draw->draw_end = W_HEIGHT - 1;
	draw->step = 1.0 * ray->texture->height / draw->line_height;
	draw->tex_pos = (draw->draw_start - W_HEIGHT / 2 + draw->line_height / 2)
		* draw->step;
}

void	draw_texture_wall(t_game *game, t_ray *ray, int x)
{
	t_draw		draw;
	int			y;
	uint32_t	color;

	init_draw_params(ray, &draw);
	y = 0;
	while (y < draw.draw_start)
	{
		mlx_put_pixel(game->img, x, y, game->ceiling_color);
		y++;
	}
	y = draw.draw_start;
	while (y < draw.draw_end)
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
