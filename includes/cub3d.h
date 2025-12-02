#ifndef CUB3D_H
# define CUB3D_H

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
# define MOUSE_SENSITIVITY 0.0008
# define COLLISION_MARGEN 0.2
# define TILE_SIZE 10     // Minimapa
# define MINIMAP_RADIUS 8 // solo lo que se ve del minimapa
# define MINI_S_X 10 
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
	double			camera_x; // Posicion en el plano de la camara
	double			ray_dir_x; // Direccion del rayo
	double			ray_dir_y;
	int				map_x; // Coordenadas del mapa
	int				map_y;
	double			side_dist_x; // Distancia al siguiente lado X/Y
	double			side_dist_y;
	double			delta_dist_x; // Distancia entre cada lado X/Y
	double			delta_dist_y;
	double			perp_wall_dist; // Distancia perpendicular a la pared
	int				step_x; // Direccion del paso (-1 o +1)
	int				step_y;
	int				hit; // flag para choque de pared
	int				side; // Lado NS o EW
	double			wall_x; //Posicion exacta donde el rayo golpea
	int				tex_x; // coordenada x en la textura
	int				tex_y; // coordenada y en la textura
	mlx_texture_t	*texture; // Textura a usar (N/S/E/W) 
}					t_ray;

typedef struct s_draw
{
	int				line_height; //Altura de la linea
	int				draw_start; // Inicio del dibujo
	int				draw_end; // Fin del dibujo
	double			step;	// Paso para recorrer textura
	double			tex_pos; // Posicion actual en textura	
}	t_draw;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	t_textures		textures;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	int				show_minimap; // add
	int				mouse_locked; // add
	int				mini_s_y; // Agregue esto por norma
	int				fd;
	char			**map;
	int				map_width; // Almacena tamaño del mapa
	int				map_height; // Almacena tamaño del mapa
}					t_game;

// Utils Function
int					print_error(char *msg);
void				path_to_null(t_game *game);

// Init Function
int					init_game(t_game *game);
int					init_graphics(t_game *game);
int					init_window(t_game *game);
int					init_player(t_game *game);
void				init_ray(t_game *game, t_ray *ray, int x);

// Parser Function
int					validate_arguments(int argc, char **argv);
int					check_extension(char *str);
int					count_lines(char *file, t_game **game);
char				*paths_of_textures(char *line, const char *name);
void				match_paths(char *line, t_game *game);
char				*paths_c_f(char *line, const char *name);
int					match_paths_c_f(char *line, t_game *game);
int					is_wall(t_game *game, double x, double y);
int					check_collision(t_game *game, double x, double y);
int					load_textures(t_game *game);
int					load_map(char *argv, t_game *game);
int					memory_map(t_game **game);
int					get_map(char *file, t_game **game);
int					check_valid_chars(char *line);
uint32_t			split_path(char *path);
uint32_t			check_path_colors(int a, int b, int c);
int					validate_char_color(char *str);
int					is_config_line(char *line);
int					is_map_line(char *line);
int					count_chars(char *line);
int					control_spaces(char *line);
int					control_empty_line(char *line);
int					validate_walls(t_game *game);
int					validate_side_walls(t_game *game);
int					validate_irregular(t_game *game);
int					check_split_rgb(char **split);
void 				get_struct_map(char *line, t_game **game, int map_started);

// Game Function
void				handle_input(t_game *game);
void				updates_game(void *param);
void				run_game(t_game *game);

// Player functions
int					player_position(t_game *game);
void				player_direction(t_game *game, char direction);
void				move_vertical(t_game *game, int direction);
void				move_side(t_game *game, int direction);
void				move_rotate(t_game *game, double angle);
void				mouse_callback(double xpos, double ypos, void *param);
void				set_direction(t_game *game, double x, double y);
// Seteo direccion del jugador
void				set_plane(t_game *game, double x, double y);
// Seteo el plano del jugador

// Minimap Functions
void				d_tile(t_game *game, int x, int y, uint32_t color);
void				d_minimap(t_game *game);
void				d_player(t_game *game);
void				d_direction(t_game *game);
uint32_t			get_tile_color(char c);
int					is_valid_map_pos(t_game *game, int map_x, int map_y);
void				draw_minimap_row(t_game *game, int map_y, int *screen_y);
void				draw_minimap_border(t_game *game);

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
void				draw_texture_wall(t_game *game, t_ray *ray, int x);
void				calculate_wall_x(t_game *game, t_ray *ray);
void				select_texture(t_game *game, t_ray *ray);
void				calculate_tex_x(t_ray *ray);
uint32_t			get_texture_color(mlx_texture_t *texture, int x, int y);

#endif
