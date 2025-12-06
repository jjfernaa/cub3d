/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:35:33 by lginer-m          #+#    #+#             */
/*   Updated: 2025/12/06 19:58:20 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parsing_textures(char *line, t_game *game, int *fd)
{
	if (is_config_line(line) == -1)
	{
		free(line);
		close(*fd);
		get_next_line(*fd);
		return (1);
	}
	match_paths(line, game);
	if (match_paths_c_f(line, game) == 1)
	{
		free(line);
		close(*fd);
		get_next_line(*fd);
		return (1);
	}
	if (is_map_line(line))
		game->map_height++;
	return (0);
}

int	count_lines(char *file, t_game **game)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("Error: Failed opening the file\n"));
	line = get_next_line(fd);
	while (line)
	{
		if (parsing_textures(line, *game, &fd) != 0)
			return (1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	get_next_line(fd);
	return (0);
}

int	memory_map(t_game *game)
{
	int	i;

	game->map = malloc((game->map_height + 1) * sizeof(char *));
	if (!game->map)
		return (1);
	i = 0;
	while (i <= game->map_height)
	{
		game->map[i] = NULL;
		i++;
	}
	return (0);
}

int	get_map(char *file, t_game *game)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("Error: Failed opening the file\n"));
	if (get_map_loop(game, fd) != 0)
	{
		close(fd);
		get_next_line(fd);
		return (1);
	}
	close(fd);
	get_next_line(fd);
	return (0);
}

int	load_map(char *argv, t_game *game)
{
	int	error;

	error = count_lines(argv, &game);
	if (error)
		return (1);
	if (game == NULL || game->map_height < 0 || game->map_width < 0
		|| (game->map_height == 0 && game->map_width == 0))
		return (1);
	if (error == 0 && memory_map(game) != 0)
		return (print_error("Error: Failed to allocate memory on map\n"));
	if (error == 0 && get_map(argv, game) != 0)
		return (print_error("Error: Failed to get map\n"));
	if (error == 0 && validate_walls(game) != 0)
		return (print_error("Error: Invalid walls\n"));
	if (error == 0 && player_position(game) != 0)
		return (print_error("Error: Player not found in map\n"));
	return (0);
}
