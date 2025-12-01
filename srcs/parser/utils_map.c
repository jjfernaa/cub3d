/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:23:55 by lginer-m          #+#    #+#             */
/*   Updated: 2025/12/01 00:10:20 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	while (line[i] && (line[i] >= 9 && line[i] <= 32))
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

int	control_spaces(char *line)
{
	int	i;
	int	start_map;

	if (!line)
		return (1);
	i = 0;
	while (line[i] && (line[i] == ' '))
		i++;
	start_map = i;
	while (line[i] && (line[i] != '\n'))
	{
		if (line[i] == ' ' && (i > start_map))
		{
			if (i > 0 && line[i - 1] != '1' && line[i - 1] != ' ')
				return (1);
			if (line[i + 1] != '\0' && line[i + 1] != '\n' && line[i + 1] != '1'
				&& line[i + 1] != ' ')
				return (1);
		}
		i++;
	}
	return (0);
}

int	control_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	return (0);
}

int	validate_irregular(t_game *game)
{
	int	y;
	int	x;
	int	len;
	int	next_len;

	y = 0;
	while (y < game->map_height - 1)
	{
		len = ft_strlen(game->map[y]);
		next_len = ft_strlen(game->map[y + 1]);
		x = 0;
		while (x < game->map_width)
		{
			if (x < len && game->map[y][x] == '0' && x >= next_len)
				return (1);
			if (x < next_len && game->map[y + 1][x] == '0' && x >= len)
				return (1);
			if (x < len && game->map[y][x] == '0')
				if (game->map[y + 1][x] == ' ' || game->map[y + 1][x] == '\n')
					return (1);
			if (x < next_len && game->map[y + 1][x] == '0')
				if (game->map[y][x] == ' ' || game->map[y][x] == '\n')
					return (1);
			x++;
		}
		y++;
	}
	return (0);
}

