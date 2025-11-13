
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
		return print_error("Error: Invalid arguments\n");
	if (check_extension(argv[1]) != 0)
		return print_error("Error: Invalid map extension\n");
	return (0);
}

/*int check_valid_chars(char *line)
{
	int i;
	int init_map;
	int real_line;

	i = 0;
	init_map = 0;
	real_line = 0;
	if(!init_map)
	{
		real_line = 1;
		while(line[i])
		{
			if(line[i] >= 9 && line[i] == 13)
				i++;
			if(line[i] != 'N' && line[i] != '1' && line[i] != '0' && line[i] != 'S' && line[i] != 'E' && line[i] != 'O' && line[i] != ' ' && line[i] != '\n' && line[i] != '\t' && line[i] != 'W')
			{
				real_line = 0;
				return print_error("Error: Invalid characters");
				break; 
			}
			i++;
		}
	if(real_line && i > 0)
		init_map = 1;
	return(0);
	}
	i = 0;
    while(line[i])
    {
        if(line[i] != 'N' && line[i] != '1' && line[i] != '0' && 
           line[i] != 'S' && line[i] != 'E' && line[i] != 'W' &&
           line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
        {
        	return print_error("Error: Invalid characters");
            break;;
        }
        i++;
    }
	return(0);
}*/
//int check_valid_paths_c_f(t_game *game); //parseo del formato de los colores, hay que procesar las ','