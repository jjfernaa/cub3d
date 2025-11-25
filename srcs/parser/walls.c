#include "../../includes/cub3d.h"

int	check_border(char *line) //para comprobar tanto las fila primera e ultima
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	validate_walls(t_game *game)
{
	int	i;
	int	height;
	int	width;

	if (!game || !game->map)
		return (1);
	height = game->map_height;
	width = game->map_width;
	if (check_border(game->map[0]) || check_border(game->map[height - 1]))
		return (print_error("Error: Border row must be surronded by walls\n"));
	i = 0;
	while (i < height)
	{
		if (game->map[i][0] != '1' || game->map[i][width - 1] != '1')
			return (print_error("Error: Side columns must be walls\n"));
		i++;
	}


	return (0);
}

void print_map(t_game *game)
{
    int i;
    int j;

    if (!game || !game->map)
    {
        printf("❌ Map is NULL\n");
        return;
    }

    printf("\n🗺️  MAP DEBUG INFO:\n");
    printf("═══════════════════════════════════════\n");
    printf("Map Height: %d\n", game->map_height);
    printf("Map Width:  %d\n", game->map_width);
    printf("═══════════════════════════════════════\n\n");

    i = 0;
    while (i < game->map_height)
    {
        if (!game->map[i])
        {
            printf("Row [%2d]: NULL ❌\n", i);
            i++;
            continue;
        }

        int len = ft_strlen(game->map[i]);
        printf("Row [%2d] (len=%2d): '", i, len);

        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == '\n')
                printf("\\n");
            else if (game->map[i][j] == '\t')
                printf("\\t");
            else if (game->map[i][j] == ' ')
                printf("·");  // Punto medio para ver espacios
            else
                printf("%c", game->map[i][j]);
            j++;
        }
        printf("'\n");

        i++;
    }
    printf("═══════════════════════════════════════\n\n");
}
int	is_wall(t_game *game, double x, double y) //FUNCION SACADA DE JUAN
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= game->map_height) //Necesito altura del mapa
		return (1);
	if (map_x < 0 || map_x >= game->map_width) //Necesito el ancho del mapa
		return (1);
	if (!game->map[map_y]) // Verifica que fila existe
		return (1);
	if (map_x >= (int)ft_strlen(game->map[map_y])) // Verifica columna
		return (1);
	if (game->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	check_collision(t_game *game, double x, double y)
{
	if (is_wall(game, x, y))
		return (1);
	if (is_wall(game, x + COLLISION_MARGEN, y))
		return (1);
	if (is_wall(game, x - COLLISION_MARGEN, y))
		return (1);
	if (is_wall(game, x, y + COLLISION_MARGEN))
		return (1);
	if (is_wall(game, x, y - COLLISION_MARGEN))
		return (1);
	return (0);
}

//comprobar en que momento se rellenan los huecos de espacios y gestionar el mapa rectangular para validar bordes irregulares(mapa rectangular)