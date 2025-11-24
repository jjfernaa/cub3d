#include "../../includes/cub3d.h"

/*
Si la fila actual es la fila 0 o la fila final, solo aceptar '1' y ' '.
De lo contrario, el primer y el último carácter siempre deben ser un '1'
En el caso de espacios en blanco no iniciales,
	los únicos caracteres aceptables adyacentes al espacio son '1' o ' '.
Si la longitud de la fila actual es mayor que la longitud de la fila superior y la columna actual es mayor que la longitud de la fila superior,
	el carácter actual debe ser '1'.
Si la longitud de la fila actual es mayor que la longitud de la fila inferior y la columna actual es mayor que la longitud de la fila inferior,
	el carácter actual debe ser '1'.
Estas reglas deben cumplir con todos los requisitos del mapa.*/

int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	while (line[i] && (line[i] >= 9 && line[i] <= 32))
		i++;
	if (line[i] == '\0' || line[i] == '\n') // Si después de los espacios no hay nada o solo newline, no es mapa
		return (0);
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

int control_spaces(char *line) //gestionar los errores fuera, no dentro
{
	int i;

	//partimos de la condicion is_map_line, por lo que no hace falta comprobar si estamos ya dentro
	if (!line)
		return (1);
	//esto te sirve para más adelante, ya que en el momento en el que aparezca una linea vacia, da ERROR	
	if(line[i] == '\0' || line[i] == '\n')
		return(1);
	i = 0;
	if((line[i + 1] == '1') && (line[i - 1] == '1' ) && i == ' ')
			i++;
	else
		return(print_error("Error: Invalid format\n"));
	
}

void	flood_fill(t_game *game, char **copy, int y, int x) //modificar para que acepte mapas irregulares
{
	if (copy[y][x] != '1')
	{
		copy[y][x] = '1' ;
		flood_fill(game, copy, y - 1, x);
		flood_fill(game, copy, y + 1, x);
		flood_fill(game, copy, y, x + 1);
		flood_fill(game, copy, y, x - 1);
	}
}

/*tambien hay que añadir el flood_fill modificado para que acepte mapas irregulares, controlar que el mapa no pueda
romperse por la mitad con lineas vacias, y controlar los espacios iniciales que estan bien*/