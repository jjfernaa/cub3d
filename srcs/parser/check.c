
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
	int	value;

	static int count = 0; // comprobar que esto sea correcto
	value = 0;
	if (!line || !line[0])
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		value = 1;
		count++;
	}
	else
		value = 0;
	if (count > 6)
	{
		print_error("Error: Invalid map format\n");
		exit(1);
	}
	return (value);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	while (line[i] && (line[i] >= 9 && line[i] <= 32))
		i++;
	if (line[i] == '1' || line[i] == '0') // la primera linea de mapa
		return (1);
	return (0);
}

int	check_valid_chars(char *line)
{
	int	i;

	if (is_config_line(line)) // comprueba las coordenadas
		return (0);
	if (!is_map_line(line)) // comprueba si hemos llegado al mapa como tal
	{
		if (line[0] == '\0' || line[0] == '\n') // si esta vacía
			return (0);
		return (print_error("Error: Invalid line of map\n"));
		exit(1);
	}
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' '
			&& line[i] != '\t' && line[i] != '\n')
			{
				print_error("Error: Invalid map character\n");
				exit(1);
			}
		i++;
	}
	if (count_chars(line))
		return (0);
	return (0);
}

int	count_chars(char *line)
{
	int			value;
	int			i;
	static int	count = 0;

	i = 0;
	value = 0;
	if (!line)
		return (0);
	while(line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
		{
			value = 1;
			count++;
		}
		else
			value = 0;
		i++;
	}
	if (count > 1)
	{
		print_error("Error: Invalid map character\n");
		exit(1);
	}
	return (value);
}
