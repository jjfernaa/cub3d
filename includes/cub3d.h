#ifndef CUB3D_h
# define CUB3D_h

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_game
{
	mlx_t	*mlx;
	int		fd;
	char	**map;

}			t_game;

void	print_error(char *msg);
int		check_extension(char *str);
int		count_lines(char *file);
#endif
