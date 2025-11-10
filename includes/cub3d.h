#ifndef CUB3D_h
# define CUB3D_h

# include "../MLX42/include/MLX42/MLX42.h"
# include "../gnl/get_next_line_bonus.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define W_WIDTH 1280
# define W_HEIGHT 1280
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define MUOSE_SENSITIVITY 0.002

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			mouse_x;
	int				first_mouse;
}					t_player;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	char			*north_path;
	char			*south_path;
	char			*east_path;
	char			*west_path;
	char			*floor;
	char			*ceiling;
}					t_textures;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	t_textures		textures;
	int				floor_color;
	int				ceiling_color;
	int				fd;
	char			**map;
}					t_game;

// Utils Function
void				print_error(char *msg);

// Init Function
int					init_game(t_game *game);
int					init_graphics(t_game *game);
int					init_window(t_game *game);
int					init_textures(t_game *game);
int					init_player(t_game *game);

// Parser Function
int					validate_arguments(int argc, char **argv);
int					check_extension(char *str);
int					count_lines(char *file, t_game *game);
char				*paths_of_textures(char *line, const char *name);
void				match_paths(char *line, t_game *game);
char				*paths_c_f(char *line, const char *name);
void				match_paths_c_f(char *line, t_game *game);

// Render Function
uint32_t			create_color(int r, int g, int b);
void				render_background(t_game *game);

// Game Function
void				move_player(t_game *game, int direction);
void				handle_input(t_game *game);
void				updates_game(void *param);
void				run_game(t_game *game);

// Cleanup Functions
void				cleanup_game(t_game *game);
void				clean_mlx(t_game *game);

#endif
