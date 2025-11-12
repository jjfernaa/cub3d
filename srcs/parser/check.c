
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
	{
		print_error("Error: Invalid arguments\n");
		return (1);
	}
	if (check_extension(argv[1]) != 0)
	{
		print_error("Error: Invalid map extension\n");
		return (1);
	}
	return (0);
}

int check_valid_chars(char *line, t_game *game)
{
	int i;
	i = 0;
	while(line[i])
	{
		if(line[i] >= 9 && line[i] == 13)
			i++;
		if(line[i] != 'N' && line[i] != '1' && line[i] != '0' && line[i] != 'S' && line[i] != 'E' && line[i] != 'O')
			print_error("Error: Invalid characters");
	}
}