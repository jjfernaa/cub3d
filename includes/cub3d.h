#ifndef CUB3D_h
# define CUB3D_h

# include "../MLX42/include/MLX42/MLX42.h"
# include "../gnl/get_next_line_bonus.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define W_WIDTH 1280
# define W_HEIGHT 720
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define MOUSE_SENSITIVITY 0.002
# define COLLISION_MARGEN 0.2
# define TILE_SIZE 10 // Minimapa
# define COL_P 0xFF0000FF // color del jugador en el minimapa

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
	char			*tmp_path;
	char			*north_path;
	char			*south_path;
	char			*east_path;
	char			*west_path;
	char			*floor;
	char			*ceiling;
}					t_textures;

typedef struct t_ray
{
	double			camera_x;  // Posicion en el plano de la camara
	double			ray_dir_x; // Direccion del rayo
	double			ray_dir_y;
	int				map_x;      // Coordenadas del mapa
	int				map_y;
	double			side_dist_x; // Distancia al siguiente lado X/Y
	double			side_dist_y;
	double			delta_dist_x; // Distancia entre cada lado X/Y
	double			delta_dist_y;
	double			perp_wall_dist; // Distancia perpendicular a la pared
	int 			step_x; // Direccion del paso (-1 o +1)
	int				step_y;
	int				hit;  // flag para choque de pared
	int				side; // Lado NS o EW
}					t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	t_textures		textures;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	int				fd;
	char			**map;
	int				map_width;  // Agrego variable para almacenar tamaño del mapa
	int				map_height; // Agrego variable para almacenar tamaño del mapa
}					t_game;

// Utils Function
int					print_error(char *msg);
void				path_to_null(t_game *game);

// Init Function
int					init_game(t_game *game);
int					init_graphics(t_game *game);
int					init_window(t_game *game);
int					init_textures(t_game *game);
int					init_player(t_game *game);
void				init_ray(t_game *game, t_ray *ray, int x);


// Parser Function
int					validate_arguments(int argc, char **argv);
int					check_extension(char *str);
int					count_lines(char *file, t_game *game);
char				*paths_of_textures(char *line, const char *name);
void				match_paths(char *line, t_game *game);
char				*paths_c_f(char *line, const char *name);
void				match_paths_c_f(char *line, t_game *game);
int					is_wall(t_game *game, double x, double y); // Agrego funcion chequeo de muro
int					load_textures(t_game *game);
int					load_map(char *argv, t_game *game);
int					memory_map(t_game *game);
int					get_map(char *file, t_game *game);
int					check_valid_chars(char *line); // Chequear si debemos borrar
uint32_t			split_path(char *path);
uint32_t			check_path_colors(int a, int b, int c);
int					validate_char_color(char *str);
void				render_background(t_game *game);

// Luego borrar

int					count_map_lines(char *file, t_game *game);

// Render Function


// Game Function
void				handle_input(t_game *game);
void				updates_game(void *param);
void				run_game(t_game *game);

// Player functions
int					player_position(t_game *game); // Agrego funcion 
void				player_direction(t_game *game, char direction); // Agrego funcion
void				move_vertical(t_game *game, int direction);
void				move_side(t_game *game, int direction);
void				move_rotate(t_game *game, double angle);
void				mouse_callback(double xpos, double ypos, void *param);
int					check_collision(t_game *game, double x, double y);
void				set_direction(t_game *game, double x, double y); // Seteo direccion del jugador
void				set_plane(t_game *game, double x, double y); // Seteo el plano del jugador

// Minimap Functions
void				d_tile(t_game *game, int x, int y, uint32_t color);
void				d_minimap(t_game *game);
void				d_player(t_game *game);
void				d_direction(t_game *game);

// Cleanup Functions
void				cleanup_game(t_game *game);
void				clean_mlx(t_game *game);
void				free_mlx_textures(t_game *game);
void				free_path_textures(t_game *game);
void				free_textures(t_game *game);
void				free_map(t_game *game);
void				free_split(char **str);

// Raycasting Functions
void				cast_rays(t_game *game);

#endif
