#ifndef CUB3D_h
# define CUB3D_h

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_game
{
	mlx_t	*mlx;
	int		fd;
	char	**map;

}			t_game;

void	print_error(char *msg);
#endif


/*typedef struct s_coor
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	mlx_texture_t	*txt_north_i;
	mlx_texture_t	*txt_south_i;
	mlx_texture_t	*txt_west_i;
	mlx_texture_t	*txt_east_i;
	mlx_texture_t	*txt_wall;

}			t_coor;*/