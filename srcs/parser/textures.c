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
		while (line[end] && line[end] != ' ' && line[end] != '\t'
			&& line[end] != '\n')
			end++;
		path = ft_substr(line, start, end - start);
		if (!path)
			return (NULL);
		return (path);
	}
	return (NULL);
}
//hay que tener en cuenta las comas en el parseo del formato del suelo y del color
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

char	*paths_of_textures(char *line, const char *name)
{
	char	*path;
	int		start;
	int		end;

	if (!line || !name)
		return (NULL);
	if (ft_strncmp(line, name, 3) == 0)
	{
		start = 3;
		while (line[start] && (line[start] == ' ' || line[start] == '\t'))
			start++;
		end = start;
		while (line[end] && line[end] != ' ' && line[end] != '\t'
			&& line[end] != '\n')
			end++;
		if (end <= start || start < 0 || end < 0)
			return (NULL);
		path = ft_substr(line, start, end - start);
		if (!path)
			return (NULL);
		return (path);
	}
	return (NULL);
}

void	match_paths(char *line, t_game *game)
{
	char	*temp_path;

	if (!game->textures.north_path)
	{
		temp_path = paths_of_textures(line, "NO ");
		if (temp_path)
			game->textures.north_path = temp_path;
	}
	if (!game->textures.south_path)
	{
		temp_path = paths_of_textures(line, "SO ");
		if (temp_path)
			game->textures.south_path = temp_path;
	}
	if (!game->textures.west_path)
	{
		temp_path = paths_of_textures(line, "WE ");
		if (temp_path)
			game->textures.west_path = temp_path;
	}
}

int	load_textures(t_game *game)
{
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.east = NULL;
	game->textures.west = NULL;
	if (!(game->textures.north = mlx_load_png(game->textures.north_path)))
		return (-1);
	if (!(game->textures.south = mlx_load_png(game->textures.south_path)))
	{
		free_mlx_textures(game);
		return (-1);
	}
	if (!(game->textures.east = mlx_load_png(game->textures.east_path)))
	{
		free_mlx_textures(game);
		return (-1);
	}
	if (!(game->textures.west = mlx_load_png(game->textures.west_path)))
	{
		free_mlx_textures(game);
		return (-1);
	}
	return (0);
}
