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
		game->map[count] = ft_strdup(line); //hago una copia para evitar segmentation fault
		count++;
		free(line);
		line = get_next_line(fd);
	}
	printf("Total: %d líneas\n", count);
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

