#include "../../includes/cub3d.h"

/*
Si la fila actual es la fila 0 o la fila final, solo aceptar '1' y ' '.
De lo contrario, el primer y el último carácter siempre deben ser un '1'
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

int control_spaces(char *line)
{
	int i;
	int start_map;

	if (!line)
		return (1);
	i = 0;
	while(line[i] && (line[i] == ' '))
		i++;
	start_map = i;
	while(line[i] && (line[i] != '\n')) //validamos espacios no iniciales
	{
		if(line[i] == ' ' && (i > start_map))
		{
			if (i > 0 && line[i - 1] != '1' && line[i - 1] != ' ')
                return (1);
            if (line[i + 1] != '\0' && line[i + 1] != '\n' && // Siguiente debe ser '1', ' ', '\n' o '\0'
                line[i + 1] != '1' && line[i + 1] != ' ')
					return (1);
		}
		i++;
	}
	return(0);
}

int control_empty_line(char *line)
{
	int i;

	i = 0;
	while(line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return(1);
	return(0);
}
