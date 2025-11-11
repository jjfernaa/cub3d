
#include "../../includes/cub3d.h"

int check_extension(char *str)
{
	int len;

	len = ft_strlen(str);
	if((len > 4) && (ft_strncmp(&str[len - 4], ".cub", 4) == 0))
		return (0);
	else
		return(1);
}

int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error("Error: Invalid arguments\n");
		return (1);
	}
	if (check_extension(argv[1]) != 1)
	{
		print_error("Error: Invalid map extension\n");
		return (1);
	}
	return (0);
}
int load_map(char *argv, t_game *game) //funcion principal donde cargaremos el mapa y vadilaremos
{
	game->height = count_lines(&argv[1], game);
	if (game == NULL || game->height < 0)
	{
		print_error("Error: Invalid map structure\n");
		return (1);
	}
	if (memory_map(game) < 0)
	{
		print_error("Error: Failed to allocate memory on map\n");
		return(1);
	}
	//gestionamos aqui el parseo del mapa
	return(0);
}


/*int check_valid_chars(char *str, t_game *game)
{
	
}*/