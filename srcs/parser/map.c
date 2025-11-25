#include "../../includes/cub3d.h"

/*
Ignorar todos los espacios en blanco iniciales.
Si la fila actual es la fila 0 o la fila final, solo aceptar '1' y ' '.
De lo contrario, el primer y el último carácter siempre deben ser un '1'
En el caso de espacios en blanco no iniciales,
	los únicos caracteres aceptables adyacentes al espacio son '1' o ' '.
Si la longitud de la fila actual es mayor que la longitud de la fila superior y la columna actual es mayor que la longitud de la fila superior,
	el carácter actual debe ser '1'.
Si la longitud de la fila actual es mayor que la longitud de la fila inferior y la columna actual es mayor que la longitud de la fila inferior,
	el carácter actual debe ser '1'.
Estas reglas deben cumplir con todos los requisitos del mapa.*/

int	count_lines(char *file, t_game *game)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("Error: Failed opening the file\n"));
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_config_line(line) == -1)
		{
			free(line);
			close(fd);
			return (-1);
		}
		match_paths(line, game);
		if (match_paths_c_f(line, game) == 1)
		{
			free(line);
			close(fd);
			return (-1);
		}
		if (is_map_line(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
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
		game->map[i] = NULL; // Lo ponemos a NULL para evitar memoria residual
		i++;
	}
	return (0);
}

int	get_map(char *file, t_game *game)
{
	int		fd;
	int		i;
	int		len;
	char	*line;
	int		map_started;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("Error: Failed opening the file\n"));
	i = 0;
	map_started = 0;
	game->map_width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
		{
			map_started = 1;
			game->map[i] = ft_strdup(line);
			len = ft_strlen(line);
			if (len > game->map_width)
				game->map_width = len;
			if (check_valid_chars(line) != 0)
			{
				free(line);
				close(fd);
				return (-1);
			}
			if (control_spaces(line) != 0)
			{
				free(line);
				close(fd);
				return (-1);
			}
			i++;
		}
		else
		{
			if (map_started && control_empty_line(line) != 0)
			{
				free(line);
				close(fd);
				return (-1);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

// funcion principal donde cargaremos el mapa y vadilaremos
int	load_map(char *argv, t_game *game)
{
	game->map_height = count_lines(argv, game);
	if (game == NULL || game->map_height < 0 || game->map_width < 0)
		return (print_error("Error: Invalid map structure\n"));
	if (memory_map(game) != 0)
		return (print_error("Error: Failed to allocate memory on map\n"));
	if (get_map(argv, game) != 0)
		return (print_error("Error: Failed to get map\n"));
	/*if (validate_walls(game) != 0)
    {
        free_map(game);
        return (print_error("Error: Invalid walls\n"));
    }*/
	print_map(game);
	printf("DEBUG: el width del mapa es: %d\n", game->map_width);
	// gestionamos aqui el parseo del mapa
	return (0);
}
