#ifndef CUB3D_h
# define CUB3D_h

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
}	t_textures;


typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	t_textures	textures;
	int			w_width;
	int			w_height;
}			t_game;

// Utils Function
void	print_error(char *msg);

// Init Function
int		init_game(t_game *game);
int		init_window(t_game *game);
int		init_textures(t_game *game);
int		init_player(t_game *game);

#endif