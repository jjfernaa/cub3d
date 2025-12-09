# cub3D

Un motor de renderizado 3D inspirado en Wolfenstein 3D, desarrollado como proyecto de 42 School.

## 📋 Descripción

cub3D es un programa que renderiza un mundo 3D en primera persona usando raycasting. El jugador puede moverse por un laberinto definido en un archivo de configuración `.cub`.

## 🎮 Características

- Renderizado 3D en tiempo real usando raycasting
- Texturas diferentes para cada orientación de pared (Norte, Sur, Este, Oeste)
- Colores configurables para suelo y techo
- Sistema de minimap
- Controles de movimiento y rotación
- Soporte para mouse

## 🛠️ Compilación

```bash
make
```

## 🚀 Uso

```bash
./cub3D <ruta_al_mapa.cub>
```

### Ejemplo:
```bash
./cub3D maps/subject_map.cub
```

## 🎯 Controles

- **W/A/S/D**: Movimiento (adelante/izquierda/atrás/derecha)
- **Flechas izquierda/derecha**: Rotación de cámara
- **ESC**: Salir del programa
- **Mouse**: Rotación de cámara

## 📁 Formato del archivo .cub

El archivo de configuración debe contener:

### Texturas (obligatorias):
```
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png
```

### Colores (obligatorios):
```
F 50,88,41          # Suelo (RGB)
C 119,170,247       # Techo (RGB)
```

### Mapa:
- `1`: Pared
- `0`: Espacio vacío
- `N/S/E/W`: Posición inicial del jugador (orientación)
- Espacios: Vacío fuera del mapa

Ejemplo:
```
1111111111111111111111111
1000000000100000000000001
1001000000000000000000001
1111111101100000000001111
1000000000110000011101111
1111011111111111110001001
1111011111111101110101001
1100000011010101110001001
1000000000000000110001001
1000N00000000000110101001
1100000111010101111101111
1111011111101011111101001
1111111111111111111111111
```

## 🔄 Flujo del Programa

### 1. **Inicialización** (`main.c`)
```
main()
  ├─> validate_arguments()     // Valida argc y extensión .cub
  ├─> init_game()               // Inicializa estructura a 0
  ├─> load_map()                // Parsea y carga el mapa
  ├─> load_textures()           // Carga texturas PNG
  ├─> init_graphics()           // Inicializa MLX42 y ventana
  └─> run_game()                // Loop principal
```

### 2. **Parsing del Mapa** (`srcs/parser/`)

#### `load_map()`:
```
load_map()
  ├─> count_lines()
  │   ├─> parsing_textures()    // Lee NO, SO, WE, EA, F, C
  │   └─> Cuenta líneas del mapa
  ├─> memory_map()              // Reserva memoria para el mapa
  ├─> get_map()                 // Llena el array del mapa
  ├─> validate_walls()          // Verifica que esté cerrado
  └─> player_position()         // Encuentra posición del jugador
```

#### Validaciones:
- `check_valid_chars()`: Solo permite `0`, `1`, `N`, `S`, `E`, `W`, espacios
- `validate_walls()`: Verifica bordes y cierre del mapa
- `validate_irregular()`: Detecta huecos en mapas irregulares
- `control_spaces()`: Verifica espacios problemáticos

### 3. **Carga de Texturas** (`srcs/parser/textures.c`)

```
load_textures()
  ├─> check_paths()             // Verifica que existan todas las rutas
  ├─> load_north_south()        // Carga texturas N y S
  ├─> load_east_west()          // Carga texturas E y W
  └─> Valida colores F y C
```

### 4. **Inicialización Gráfica** (`srcs/execution/init.c`)

```
init_graphics()
  ├─> init_window()
  │   ├─> mlx_init()            // Inicializa MLX42
  │   ├─> mlx_new_image()       // Crea imagen principal
  │   └─> mlx_image_to_window() // Muestra imagen
  └─> init_player()
      └─> Inicializa posición mouse y flags
```

### 5. **Game Loop** (`srcs/execution/game_loop.c`)

```
run_game()
  └─> mlx_loop()
      └─> game_loop() [cada frame]
          ├─> handle_movement()     // Procesa WASD
          ├─> handle_rotation()     // Procesa flechas/mouse
          ├─> render_frame()
          │   ├─> raycast_render()  // Renderiza paredes 3D
          │   └─> render_minimap()  // Renderiza minimap 2D
          └─> mlx_put_pixel()       // Dibuja en pantalla
```

### 6. **Raycasting** (`srcs/execution/raycasting.c`)

Para cada columna de píxeles (x):
```
raycast_render()
  └─> Para cada x en [0, W_WIDTH]:
      ├─> init_ray()            // Inicializa rayo
      ├─> calculate_step()      // Calcula dirección DDA
      ├─> perform_dda()         // Algoritmo DDA hasta hit
      ├─> calculate_wall()      // Calcula altura de pared
      └─> draw_textured_line()  // Dibuja columna con textura
```

#### Texturizado (`srcs/execution/raycast_texture.c`):
```
draw_textured_line()
  ├─> select_texture()          // Elige textura según orientación
  ├─> calculate_texture_x()     // Coordenada X en textura
  └─> Para cada y:
      ├─> calculate_texture_y() // Coordenada Y en textura
      ├─> get_texture_color()   // Obtiene color del pixel
      └─> mlx_put_pixel()       // Dibuja pixel
```

### 7. **Minimap** (`srcs/execution/minimap.c`)

```
render_minimap()
  ├─> draw_minimap_background() // Fondo semitransparente
  ├─> draw_minimap_tiles()      // Dibuja paredes y suelo
  └─> draw_player_icon()        // Dibuja jugador en minimap
```

### 8. **Cleanup** (`srcs/parser/free.c`)

```
cleanup_game()
  ├─> free_textures()           // Libera strings de rutas
  ├─> free_map()                // Libera array del mapa
  └─> clean_mlx()
      ├─> mlx_delete_image()    // Elimina imágenes
      ├─> mlx_delete_texture()  // Elimina texturas
      └─> mlx_terminate()       // Cierra MLX42
```

## 📂 Estructura del Proyecto

```
cub3d/
├── includes/
│   └── cub3d.h                 # Estructuras y prototipos
├── srcs/
│   ├── main.c                  # Punto de entrada
│   ├── parser/
│   │   ├── map.c               # Parsing del mapa
│   │   ├── parser_map.c        # Helpers de parsing
│   │   ├── textures.c          # Parsing de texturas/colores
│   │   ├── images.c            # Carga de PNG
│   │   ├── check.c             # Validaciones
│   │   ├── walls.c             # Validación de paredes
│   │   ├── color.c             # Parsing de colores RGB
│   │   ├── utils.c             # Utilidades generales
│   │   ├── utils_map.c         # Utilidades del mapa
│   │   └── free.c              # Gestión de memoria
│   └── execution/
│       ├── init.c              # Inicialización
│       ├── game_loop.c         # Loop principal
│       ├── raycasting.c        # Motor de raycasting
│       ├── raycast_render.c    # Renderizado de paredes
│       ├── raycast_texture.c   # Texturizado
│       ├── player.c            # Lógica del jugador
│       ├── moves.c             # Movimiento
│       └── minimap.c           # Minimap
├── libft/                      # Librería personal
├── gnl/                        # Get Next Line
├── MLX42/                      # Librería gráfica
├── maps/                       # Mapas de ejemplo
├── textures/                   # Texturas PNG
└── Makefile
```

## 🧪 Validación de Memoria

El proyecto está libre de memory leaks (verificado con valgrind):

```bash
valgrind --leak-check=full --show-leak-kinds=definite ./cub3D maps/subject_map.cub
```

**Resultado esperado:**
```
definitely lost: 0 bytes in 0 blocks
```

## 📝 Normas

- Cumple con la Norminette de 42
- Máximo 25 líneas por función
- Máximo 5 funciones por archivo
- Sin variables globales
- Gestión correcta de memoria (sin leaks)

## 👥 Autores

- **lginer-m** - Parser, validaciones, gestión de memoria
- **juan-jof** - Raycasting, renderizado, controles

---

**Proyecto desarrollado en 42 Málaga** 🚀
