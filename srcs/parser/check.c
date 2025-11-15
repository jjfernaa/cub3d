
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

static int	is_config_line(char *line)
{
	if(!line || !line[0])
		return(0);
	if(ft_strncmp(line, "NO ", 3) == 0)
		return(1);
	if(ft_strncmp(line, "SO ", 3) == 0)
		return(1);
	if(ft_strncmp(line, "WE ", 3) == 0)
		return(1);
	if(ft_strncmp(line, "EA ", 3) == 0)
		return(1);
	if(ft_strncmp(line, "F ", 2) == 0)
		return(1);
	if(ft_strncmp(line, "C ", 2) == 0)
		return(1); //validacion, no error
	return(0);
}

static int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0])
		return(0);
	i = 0;
	while(line[i] && (line[i] >= 9 && line[i] <= 32))
		i++;
	if(line[i] == '1' || line[i] == '0')
		return(1);
	return (0);
}

int	check_valid_chars(char *line) //no estoy al 100% segura si esto es correcto
{
	int	i;

	if(is_config_line(line))
		return(0); 
	if(!is_map_line(line)) //en el momento en el que empiece a contar 0 o 1 ya estamos en el mapa
		return(0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' '
			&& line[i] != '\t' && line[i] != '\n')
			return (print_error("Error: Invalid map character\n"));
		i++;
	}
	return (0);
}

//HAY QUE PARSEAR QUE ESTEN TODAS LAS COORDENADAS POR IGUAL