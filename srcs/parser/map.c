/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:00:12 by lginer-m          #+#    #+#             */
/*   Updated: 2025/11/08 19:45:06 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
Ignorar todos los espacios en blanco iniciales.
Si la fila actual es la fila 0 o la fila final, solo aceptar '1' y ' '.
De lo contrario, el primer y el último carácter siempre deben ser un '1'
En el caso de espacios en blanco no iniciales, los únicos caracteres aceptables adyacentes al espacio son '1' o ' '.
Si la longitud de la fila actual es mayor que la longitud de la fila superior y la columna actual es mayor que la longitud de la fila superior, el carácter actual debe ser '1'.
Si la longitud de la fila actual es mayor que la longitud de la fila inferior y la columna actual es mayor que la longitud de la fila inferior, el carácter actual debe ser '1'.
Estas reglas deben cumplir con todos los requisitos del mapa.*/

int	count_lines(char *file)
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
		if(ft_strncmp(&line, "NO ", 3) == 0)
		//printf("mapa: %s\n", line);  //imprime el mapa
		count++;
		free(line);
		line = get_next_line(fd);

	}
	close(fd);
	return (count);
}

int paths_of_textures(char *line, t_game *game) //gestionarlo en otra funcion principal para acortar lineas
{
	char *path;
	int start;
	int end;
	int i;

	i = 0;
	while(line[i])
	{
		if(ft_strncmp(&line[i], "NO ", 3) == 0)
		{
			start = 3;
			while(line[start] && (line[start] >= 9 && line[start] <= 13)) //salta espacios iniciales
				start++;
			end = start;
			while(line[end] && (line[end] >= 9 && line[end] <= 13))
				end++;
			path = ft_substr(line, start, end - start); //para mi esto no tiene sentido
			if(!path)
				return(-1);
		}
		i++;
	}
	return(0);
}
	
int load_textures(char *path, t_game *game)
{
	if(!(game->textures.north = mlx_load_texture(path))) //load_textures
	{
		free(path);
		return(-1);
	}
	free(path);

	/* para poder gestionar más adelante en el parser:
		if(load_textures(path, game) <= 0)
			print_error("Error: textures are not loading");
	*/
}