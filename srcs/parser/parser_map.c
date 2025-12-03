/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:35:42 by lginer-m          #+#    #+#             */
/*   Updated: 2025/12/03 19:35:43 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	validate_map_line(char *line, int *fd)
{
	if (check_valid_chars(line) != 0)
	{
		free(line);
		close(*fd);
		return (-1);
	}
	if (control_spaces(line) != 0)
	{
		free(line);
		close(*fd);
		return (-1);
	}
	return (0);
}

int	process_map_line(char *line, t_game *game, int *i, int *fd)
{
	int	len;

	game->map[*i] = ft_strdup(line);
	len = ft_strlen(line);
	if (len > game->map_width)
		game->map_width = len;
	if (validate_map_line(line, fd) != 0)
		return (-1);
	(*i)++;
	return (0);
}

int	handle_non_map_line(char *line, int map_started, int *fd)
{
	if (map_started && control_empty_line(line) != 0)
	{
		free(line);
		close(*fd);
		return (-1);
	}
	return (0);
}

int	get_map_loop(t_game *game, int fd)
{
	int		i;
	char	*line;
	int		map_started;

	i = 0;
	map_started = 0;
	game->map_width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
		{
			map_started = 1;
			if (process_map_line(line, game, &i, &fd) != 0)
				return (1);
		}
		else if (handle_non_map_line(line, map_started, &fd) != 0)
			return (1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
