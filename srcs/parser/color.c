#include "../../includes/cub3d.h"

int parser_color(t_game *game)
{
	if((split_path_c(game) != 0) || (split_path_f(game) != 0))
		return (print_error("Error: Failed incident to get color\n"));
}

int split_path_c(t_game *game)
{
	char *path_c;
	char *split_c;

	path_c = game->textures.ceiling;
	if(!game->textures.ceiling || !path_c)
		return(print_error("Error: Ceiling path are not loading\n"));
	
	split_c = ft_split(path_c, ',');
	printf("Valor path_c: %s\n", split_c);

	return(0);
}

int	split_path_f(t_game *game)
{
	char *path_f;
	char *split_f;
	
	path_f = game->textures.floor;
	if(!game->textures.floor || !path_f)
		return(print_error("Error: Floor path are not loading\n"));
	
	split_f = ft_split(path_f, ',');
	printf("Valor path_f: %s\n", split_f);

	return(0);
}