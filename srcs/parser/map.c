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

	//printf("Intentando abrir: '%s'\n", file);
	fd = open(file, O_RDONLY);
	//printf("valor fd: %d\n", fd);
	if(fd < 0)
		print_error("Error: Failed opening the file\n");
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

	game->map = malloc((game->height + 1) * sizeof(char *));
	if (!game->map)
		return (1);
	i = 0;
	while (i <= game->height)
	{
		game->map[i] = NULL; //Lo ponemos a NULL para evitar memoria residual
		i++;
	}
	return (0);
}

int get_map(char *file, t_game *game) //funciona, pero hay que rescribir un poco en funcion del propposito de la funcion
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if(fd < 0)
		print_error("Error: Failed opening the file\n");
	i = 0;
	line = get_next_line(fd);
	while(line)
	{
		game->map[i] = ft_strdup(line); //copia para evitar segmentation fault
		check_valid_chars(line, game);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return(i);
}
int	load_map(char *argv, t_game *game) // funcion principal donde cargaremos el mapa y vadilaremos		
{
	game->height = count_lines(argv, game);
	if(game == NULL || game->height < 0)
	{
		print_error("Error: Invalid map structure\n");
		return (1);
	}
	if(memory_map(game) != 0)
	{
		print_error("Error: Failed to allocate memory on map\n");
		return (1);
	}
	if(get_map(argv, game) != 0)
	{
		print_error("Error: Failed to get map\n");
		return (1);
	}
	// gestionamos aqui el parseo del mapa
	return (0);
}