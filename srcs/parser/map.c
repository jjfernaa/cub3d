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

	// printf("Intentando abrir: '%s'\n", file);
	fd = open(file, O_RDONLY);
	// printf("valor fd: %d\n", fd);
	if (fd < 0)
		return (print_error("Error: Failed opening the file\n"));
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		match_paths(line, game);
		match_paths_c_f(line, game);
		// luego gestionas las texturas A PARTE(O NO)
		// Solo contar líneas que sean realmente del mapa
		if (is_map_start(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	// printf("Total: %d líneas\n", count);
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
// Función auxiliar para verificar si una línea es parte del mapa real
int	is_map_start(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	// Saltar espacios en blanco iniciales
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	// Si la línea está vacía o es solo whitespace
	if (!line[i] || line[i] == '\n')
		return (0);
	// Si es una línea de configuración (NO, SO, WE, EA, F, C)
	if (ft_strncmp(line + i, "NO ", 3) == 0 || ft_strncmp(line + i, "SO ",
			3) == 0 || ft_strncmp(line + i, "WE ", 3) == 0 || ft_strncmp(line
			+ i, "EA ", 3) == 0 || ft_strncmp(line + i, "F ", 2) == 0
		|| ft_strncmp(line + i, "C ", 2) == 0)
		return (0);
	// Si contiene caracteres del mapa (1, 0, espacio, N, S, E, W)
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == ' ' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			return (1);
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

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("Error: Failed opening the file\n"));
	i = 0;
	game->map_width = 0;
	line = get_next_line(fd);
	while (line)
	{
		// Solo procesar líneas que sean realmente del mapa
		if (is_map_start(line))
		{
			game->map[i] = ft_strdup(line);
			// copia para evitar segmentation fault
			len = ft_strlen(line);
			if (len > game->map_width) // Encontrar el ancho maximo
				game->map_width = len;
			check_valid_chars(line);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}
// funcion principal donde cargaremos el mapa y vadilaremos
int	load_map(char *argv, t_game *game)
{
	game->map_height = count_lines(argv, game);
	if (game == NULL || game->map_height < 0 || game->map_width < 0)
		return (print_error("Error: Invalid map structure\n"));
	if (memory_map(game) != 0)
		return (print_error("Error: Failed to allocate memory on map\n"));
	if (get_map(argv, game) <= 0)
		return (print_error("Error: Failed to get map\n"));
	// gestionamos aqui el parseo del mapa
	return (0);
}

/*Hay que controlar que no se puedan poner algo más que no sean coordenadas en el inicio,
gestionar tambien que solo existan un solo tipo de	coordenada(que no haya dos NO). Tambien que solo aparezca una N,E,S
en el mapa, que no haya repeticiones,
	como tambien hay que añadir el flood_fill modificado para que acepte mapas irregulares,*/