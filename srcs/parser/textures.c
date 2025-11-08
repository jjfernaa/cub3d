/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:17:16 by lginer-m          #+#    #+#             */
/*   Updated: 2025/11/08 21:34:22 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*paths_c_f(char *line, const char *name)
{
	char	*path;
	int		start;
	int		end;

	if (ft_strncmp(line, name, 2) == 0)
	{
		start = 2;
		while (line[start] && (line[start] == ' ' || line[start] == '\t'))
			start++;
		end = start;
		while(line[end] && line[end] != ' ' && line[end] != '\t' && line[end] != '\n')
			end++;
		path = ft_substr(line, start, end - start);
		if(!path)
			return (NULL);
		return (path);
	}
	return (NULL);
}

void	match_paths_c_f(char *line, t_game *game)
{
	char	*temp_path;

	if (!game->textures.east_path)
	{
		temp_path = paths_of_textures(line, "EA ");
		if (temp_path)
			game->textures.east_path = temp_path;
	}
	if (!game->textures.ceiling)
	{
		temp_path = paths_c_f(line, "C ");
		if (temp_path)
			game->textures.ceiling = temp_path;
	}
	if (!game->textures.floor)
	{
		temp_path = paths_c_f(line, "F ");
		if (temp_path)
			game->textures.floor = temp_path;
	}
}
