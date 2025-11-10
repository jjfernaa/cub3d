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
	close(fd);
	return(count);
}

char	*paths_of_textures(char *line, const char *name)
{
	char	*path;
	int		start;
	int		end;

	if (ft_strncmp(line, name, 3) == 0)
	{
		start = 3;
		while(line[start] && (line[start] == ' ' || line[start] == '\t'))
			start++;
		end = start;
		while(line[end] && line[end] != ' ' && line[end] != '\t' && line[end] != '\n')
			end++;
		path = ft_substr(line, start, end - start);
		if(!path)
			return(NULL);
		return(path);
	}
	return (NULL);
}

void	match_paths(char *line, t_game *game)
{
	char *temp_path;
	
	if(!game->textures.north_path)
	{
		temp_path = paths_of_textures(line, "NO ");
		if(temp_path)
			game->textures.north_path = temp_path;
	}
	if(!game->textures.south_path)
	{
		temp_path = paths_of_textures(line, "SO ");
		if(temp_path)
			game->textures.south_path = temp_path;
	}
	if(!game->textures.west_path)
	{
		temp_path = paths_of_textures(line, "WE ");
		if(temp_path)
			game->textures.west_path = temp_path;
	}
}

/*int load_textures(char *path, t_game *game)
{
	if(!(game->textures.north = mlx_load_png(game->textures.north_path)))
	{
		free(game->textures.north_path); //poner el free_textures en este lugar
		return(-1);
	}
	if(!(game->textures.south = mlx_load_png(game->textures.south_path)))
	{
		free(game->textures.north_path); //poner el free_textures en este lugar
		return(-1);
	}
	free(path);
		para poder gestionar más adelante en el parser:
		if(load_textures(path, game) <= 0)
			print_error("Error: textures are not loading");
}*/
