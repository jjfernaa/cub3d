/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 20:14:09 by juan-jof          #+#    #+#             */
/*   Updated: 2025/12/03 20:14:10 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	return (0);
}

int	init_window(t_game *game)
{
	game->mlx = mlx_init(W_WIDTH, W_HEIGHT, "cub3D", true);
	if (!game->mlx)
		return (print_error("Error: Failed to initialize MLX\n"));
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	if (!game->img)
	{
		mlx_terminate(game->mlx);
		return (print_error("Error: Failed to create image\n"));
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		mlx_delete_image(game->mlx, game->img);
		mlx_terminate(game->mlx);
		return (print_error("Error: Failed to display image\n"));
	}
	game->mini_s_y = (W_HEIGHT - (MINIMAP_RADIUS * 2 + 1)
			* TILE_SIZE - 10);
	return (0);
}

int	init_graphics(t_game *game)
{
	if (init_window(game) != 0)
		return (-1);
	if (init_player(game) != 0)
	{
		clean_mlx(game);
		return (-1);
	}
	return (0);
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)W_WIDTH - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}
