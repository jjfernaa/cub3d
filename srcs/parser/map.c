#include "../../includes/cub3d.h"

static int	parsing_textures(char *line, t_game **game, int fd)
{
	if (is_config_line(line) == -1)
	{
		free(line);
		close(fd);
		return (1);
	}
	match_paths(line, *game);
	if (match_paths_c_f(line, *game) == 1)
	{
		free(line);
		close(fd);
		return (1);
	}
	if (is_map_line(line))
		(*game)->map_height++;
	return (0);
}

static int	parsing_map_lines(char *line, int fd, int map_started)
{
	if (is_map_line(line))
	{
		if (check_valid_chars(line) != 0)
		{
			free(line);
			close(fd);
			return (1);
		}
		if (control_spaces(line) != 0)
		{
			free(line);
			close(fd);
			return (1);
		}
	}
	else
	{
		if (map_started && control_empty_line(line) != 0)
		{
			free(line);
			close(fd);
			return (1);
		}
	}
	return (0);
}

void	get_struct_map(char *line, t_game **game, int map_started)
{
	int	i;
	int	len;

	(*game)->map_width = 0;
	i = 0;
	while (is_map_line(line))
	{
		map_started = 1;
		(*game)->map[i] = ft_strdup(line);
		len = ft_strlen(line);
		if (len > (*game)->map_width)
		(*game)->map_width = len;
		i++;
	}
	return ;
}

int	memory_map(t_game **game)
{
	int	i;

	(*game)->map = malloc(((*game)->map_height + 1) * sizeof(char *));
	if (!(*game)->map)
		return (1);
	i = 0;
	while (i <= (*game)->map_height)
	{
		(*game)->map[i] = NULL;
		i++;
	}
	return (0);
}
int	count_lines(char *file, t_game **game)
{
	int		fd;
	char	*line;
	int		map_started;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("Error: Failed opening the file\n"));
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if(parsing_textures(line, game, fd))
			return(1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	get_map(char *file, t_game **game)
{
	int		fd;
	char	*line;
	int		map_started;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("Error: Failed opening the file\n"));
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		get_struct_map(line, game, map_started);
		if(parsing_map_lines(line, fd, map_started))
			return(1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
} 
int	load_map(char *argv, t_game *game)
{
	int error;

	error = count_lines(argv, &game);
	if (error)
		return (1);
	if (game == NULL || game->map_height < 0 || game->map_width < 0)
		return (print_error("Error: Invalid map structure\n"));
	if(memory_map(&game) != 0)
		print_error("Error: Failed to allocate memory on map\n");
	 if (error == 0 && get_map(argv, &game) != 0)
		return (print_error("Error: Failed to get map\n"));
	if (error == 0 && validate_walls(game) != 0)
		return (print_error("Error: Invalid walls\n"));
	return (0);
}
