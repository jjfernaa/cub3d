#include "../../includes/cub3d.h"

int	check_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if ((len > 4) && (ft_strncmp(&str[len - 4], ".cub", 4) == 0))
		return (0);
	else
		return (1);
}

int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
		return (print_error("Error: Invalid arguments\n"));
	if (check_extension(argv[1]) != 0)
		return (print_error("Error: Invalid map extension\n"));
	return (0);
}

int	is_config_line(char *line)
{
	static int count = 0;

	if (!line || !line[0])
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		count++;
		if (count > 6)
			return (-1);
		return (1);
	}
	return (0);
}

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

int	check_valid_chars(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' '
			&& line[i] != '\n')
			return (print_error("Error: Invalid map character\n"));
		i++;
	}
	if (count_chars(line) != 0)
		return (1);
	return (0);
}

int	count_chars(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			count++;
		i++;
	}
	if (count > 1)
		return (print_error("Error: Multiple player positions in line\n"));
	return (0);
}

/*Hay que modificar count_chars y el bucle de check_valid_chars, meter esas dos quitando
el bucle y meterlo en una funcion nueva para ahorras lineas de la norma*/