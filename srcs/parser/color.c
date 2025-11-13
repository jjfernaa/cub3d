#include "../../includes/cub3d.h"

int parser_color(t_game *game)
{
	if((split_path_c(game) != 0) || (split_path_f(game) != 0))
		return (print_error("Error: Failed incident to get color\n"));
	return(0);
}
static void free_split(char **str)
{
	int i;

	if(str)
    {
        i = 0;
        while(str[i])
    	    free(str[i++]);
        free(str);
    }
}
int split_path_c(t_game *game)
{
	char **split_c;
	char **split_f;
	int r;
	int g;
	int b;

	r = 0;
	g = 0;
	b = 0;
	if(!game->textures.ceiling || !game->textures.floor)
		return(print_error("Error: Paths are not loading\n"));
	if(game->textures.ceiling)
		split_c = ft_split(game->textures.ceiling, ',');
	if(!split_c || !split_c[0] || !split_c[1] || !split_c[2])
	{
		free_split(split_c);
		return(1);
	}
	r = ft_atoi(split_c[0]);
	g = ft_atoi(split_c[1]);
	b = ft_atoi(split_c[2]);

	
	/*printf("Ceiling colors: %s\n", game->textures.ceiling);
	while(split_c[i])
    {
        printf("[%s] ", split_c[i]);  // ✅ Cada elemento entre corchetes
        i++;
    }*/
   	free_split(split_c);
	return(0);
}

int	split_path_f(t_game *game)
{
	char *path_f;
	char **split_f;
	//int i = 0;
	
	path_f = game->textures.floor;
	if(!game->textures.floor || !path_f)
		return(print_error("Error: Floor path are not loading\n"));
	
	split_f = ft_split(path_f, ',');
 	/*printf("Floor colors: %s\n", path_f);
	while(split_f[i])
    {
        printf("[%s] ", split_f[i]);  // ✅ Cada elemento entre corchetes
        i++;
    }*/
   
	return(0);
}



/*int check_path_colors(int a, int b, int c)
{
	if(!a || !b || !c)
	{
		printf("la has cagado con el atoi guapa\n"); //BORRAR DESPUES
		return(1);
	}
	if(!(a >= 0 && a <= 255) && (b >= 0 && b <= 255) && (c >= 0 && c <= 255))
		
}*/

//añadir una variable color donde se almacene el valor int ya spliteado y conertido a int obviamente



// Añadir en textures.c:
int parse_color_value(char *str)
{
    char    **split;
    int     r, g, b;
    int     color;

    split = ft_split(str, ',');
    if (!split || !split[0] || !split[1] || !split[2])
    {
        // free split si es necesario
        return (-1);
    }
    
    r = ft_atoi(split[0]);
    g = ft_atoi(split[1]);
    b = ft_atoi(split[2]);
    
    // Liberar split
    int i = 0;
    while (split[i])
        free(split[i++]);
    free(split);
    
    // Validar rangos
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (-1);
    
    // Convertir a formato MLX (RGBA)
    color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
    return (color);
}