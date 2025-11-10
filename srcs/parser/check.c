
#include "../../includes/cub3d.h"

int check_extension(char *str)
{
	int len;

	len = ft_strlen(str);
	if((len > 4) && (ft_strncmp(&str[len - 4], ".cub", 4) == 0))
		return (1);
	else
		return(-1);
}

int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error("Error: Invalid arguments\n");
		return (-1);
	}
	if (check_extension(argv[1]) != 1)
	{
		print_error("Error: Invalid map extension\n");
		return (-1);
	}
	return (0);
}