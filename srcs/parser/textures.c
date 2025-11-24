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

int	match_paths_c_f(char *line, t_game *game)
{
	if (!game->textures.ceiling)
	{
		game->textures.tmp_path = paths_c_f(line, "C ");
		if (game->textures.tmp_path)
		{
			game->textures.ceiling = game->textures.tmp_path;
			game->ceiling_color = split_path(game->textures.ceiling);
			if (game->ceiling_color == 1)
				return (print_error("Error: Invalid ceiling color format\n"));
		}
	}
	if (!game->textures.floor)
	{
		game->textures.tmp_path = paths_c_f(line, "F ");
		if (game->textures.tmp_path)
		{
			game->textures.floor = game->textures.tmp_path;
			game->floor_color = split_path(game->textures.floor);
			if (game->floor_color == 1)
				return (print_error("Error: Invalid floor color format\n"));
		}
	}
	return (0);
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
	if (!game->textures.north_path)
	{
		game->textures.tmp_path = paths_of_textures(line, "NO ");
		if (game->textures.tmp_path)
			game->textures.north_path = game->textures.tmp_path;
	}
	if (!game->textures.south_path)
	{
		game->textures.tmp_path = paths_of_textures(line, "SO ");
		if (game->textures.tmp_path)
			game->textures.south_path = game->textures.tmp_path;
	}
	if (!game->textures.west_path)
	{
		game->textures.tmp_path = paths_of_textures(line, "WE ");
		if (game->textures.tmp_path)
			game->textures.west_path = game->textures.tmp_path;
	}
	if (!game->textures.east_path)
	{
		game->textures.tmp_path = paths_of_textures(line, "EA ");
		if (game->textures.tmp_path)

			game->textures.east_path = game->textures.tmp_path;
	}
}

int	load_textures(t_game *game)
{
	if (!(game->textures.north = mlx_load_png(game->textures.north_path)))
		return (print_error("Error: North texture are not found\n"));
	if (!(game->textures.south = mlx_load_png(game->textures.south_path)))
	{
		free_mlx_textures(game);
		return (print_error("Error: South texture are not found\n"));
	}
	if (!(game->textures.east = mlx_load_png(game->textures.east_path)))
	{
		free_mlx_textures(game);
		return (print_error("Error: East texture are not found\n"));
	}
	if (!(game->textures.west = mlx_load_png(game->textures.west_path)))
	{
		free_mlx_textures(game);
		return (print_error("Error: West texture are not found\n"));
	}
	return (0);
}

// CONTROLAR QUE al poner una coordenada distinta hace segmentation fault