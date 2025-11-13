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
# define W_HEIGHT 720
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define MOUSE_SENSITIVITY 0.002

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
	int				map_width; // Agrego variable para almacenar tamaño del mapa
	int				map_height; // Agrego variable para almacenar tamaño del mapa
}					t_game;

// Utils Function
int				print_error(char *msg);
void				path_to_null(t_game *game);

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
int					is_wall(t_game *game, double x, double y); // Agrego funcion chequeo de muro
int 				load_textures(t_game *game);
int 				load_map(char *argv, t_game *game);
int					memory_map(t_game *game);
int					get_map(char *file, t_game *game);
int					check_valid_chars(char *line);
int 				split_path_c(t_game *game);
int					split_path_f(t_game *game);
int 				parser_color(t_game *game);

// Render Function
uint32_t			create_color(int r, int g, int b);
void				render_background(t_game *game);

// Game Function
void				handle_input(t_game *game);
void				updates_game(void *param);
void				run_game(t_game *game);

// Movement functions
void	move_vertical(t_game *game, int direction);
void	move_side(t_game *game, int direction);
void	move_rotate(t_game *game, double angle);
void	mouse_callback(double xpos, double ypos, void *param);

// Cleanup Functions
void				cleanup_game(t_game *game);
void				clean_mlx(t_game *game);
void 				free_mlx_textures(t_game *game);
void 				free_path_textures(t_game *game);
void				free_textures(t_game *game);
void				free_map(t_game *game);


#endif
