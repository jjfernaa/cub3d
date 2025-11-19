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

/* int	count_lines(char *file, t_game *game)
{
	int		fd;
	int		count;
	char	*line;

	//printf("Intentando abrir: '%s'\n", file);
	fd = open(file, O_RDONLY);
	//printf("valor fd: %d\n", fd);
	if(fd < 0)
		return (print_error("Error: Failed opening the file\n"));
	count = 0;
	line = get_next_line(fd);
	while(line)
	{
		match_paths(line, game);
		match_paths_c_f(line, game);//luego gestionas las texturas A PARTE(O NO)
		count++;
		free(line);
		line = get_next_line(fd);
	}
	//printf("Total: %d líneas\n", count);
	close(fd);
	return(count);
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
		game->map[i] = NULL; //Lo ponemos a NULL para evitar memoria residual
		i++;
	}
	return (0);
}
//funciona, pero hay que rescribir un poco en funcion del propposito de la funcion
int	get_map(char *file, t_game *game)
{
	int		fd;
	int		i;
	int		len;
	char	*line;

	fd = open(file, O_RDONLY);
	if(fd < 0)
		return (print_error("Error: Failed opening the file\n"));
	i = 0;
	game->map_width = 0;
	line = get_next_line(fd);
	while(line)
	{
		game->map[i] = ft_strdup(line); //copia para evitar segmentation fault
		len = ft_strlen(line);
		if (len > game->map_width) // Encontrar el ancho maximo
			game->map_width = len;
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return(i);
}
// funcion principal donde cargaremos el mapa y vadilaremos
int	load_map(char *argv, t_game *game)
{
	game->map_height = count_lines(argv, game);
	if(game == NULL || game->map_height < 0 || game->map_width < 0)
		return (print_error("Error: Invalid map structure\n"));
	if(memory_map(game) != 0)
		return (print_error("Error: Failed to allocate memory on map\n"));
	if(get_map(argv, game) <= 0)
		return (print_error("Error: Failed to get map\n"));
	// gestionamos aqui el parseo del mapa
	return (0);
}  */

// 🛑⚠️ Arego este cambio, luego borrar ⚠️🛑

#include "../../includes/cub3d.h"

/*
** is_config_complete - Verifica si todas las texturas están cargadas
*/
static int	is_config_complete(t_game *game)
{
    if (!game->textures.north_path || !game->textures.south_path
        || !game->textures.east_path || !game->textures.west_path
        || !game->textures.floor || !game->textures.ceiling)
        return (0);
    return (1);
}

/*
** is_map_start - Detecta si la línea es el inicio del mapa
*/
static int	is_map_start(char *line)
{
    int	i;

    if (!line || !line[0])
        return (0);
    i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    if (line[i] == '1')
        return (1);
    return (0);
}

/*
** load_config - Lee solo la configuración (texturas y colores)
*/
static int	load_config(int fd, t_game *game)
{
    char	*line;
    //int		map_started;

    //map_started = 0;
    line = get_next_line(fd);
    while (line)
    {
        // Detectar si empezó el mapa
        if (is_map_start(line))
        {
            free(line);
            break ;
        }
        
        // Procesar líneas de configuración
        match_paths(line, game);
        match_paths_c_f(line, game);
        
        free(line);
        line = get_next_line(fd);
    }
    
    // Verificar que toda la config está completa
    if (!is_config_complete(game))
        return (print_error("Error: Missing texture or color configuration\n"));
    
    return (0);
}

/*
** count_map_lines - Cuenta SOLO líneas del mapa (después de config)
*/
int	count_map_lines(char *file, t_game *game)
{
    int		fd;
    int		count;
    char	*line;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (print_error("Error: Failed opening the file\n"));
    // 1. Cargar configuración primero
    if (load_config(fd, game) != 0)
    {
        close(fd);
        return (-1);
    }
    // 2. Contar líneas del mapa
    count = 0;
    line = get_next_line(fd);
    while (line)
    {
        if (is_map_start(line) || count > 0)  // Si ya empezó el mapa
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
        game->map[i] = NULL;
        i++;
    }
    return (0);
}

/*
** skip_to_map - Salta las líneas de configuración hasta llegar al mapa
*/
static void	skip_to_map(int fd)
{
    char	*line;

    line = get_next_line(fd);
    while (line)
    {
        if (is_map_start(line))
        {
            free(line);
            break ;
        }
        free(line);
        line = get_next_line(fd);
    }
}

/*
** get_map - Lee SOLO las líneas del mapa
*/
int	get_map(char *file, t_game *game)
{
    int		fd;
    int		i;
    int		len;
    char	*line;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (print_error("Error: Failed opening the file\n"));
    
    // Saltar configuración
    skip_to_map(fd);
    
    i = 0;
    game->map_width = 0;
    line = get_next_line(fd);
    while (line)
    {
        // Validar caracteres
        if (check_valid_chars(line) != 0)
        {
            free(line);
            close(fd);
            return (-1);
        }
        
        game->map[i] = ft_strdup(line);
        len = ft_strlen(line);
        if (len > game->map_width)
            game->map_width = len;
        i++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (i);
}

/*
** load_map - Función principal para cargar el mapa
*/
int	load_map(char *argv, t_game *game)
{
    game->map_height = count_map_lines(argv, game);
    if (game->map_height < 0)
        return (print_error("Error: Invalid map structure\n"));
    if (memory_map(game) != 0)
        return (print_error("Error: Failed to allocate memory on map\n"));
    if (get_map(argv, game) <= 0)
        return (print_error("Error: Failed to get map\n"));
    return (0);
}