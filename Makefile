NAME := cub3D
CC := cc
CFLAGS := -g -Wall -Werror -Wextra \
		#-fsanitize=address,undefined \
		#-Wunreachable-code -Ofast \

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
GNL_DIR := gnl
MLX42_DIR := MLX42
MLX42 := $(MLX42_DIR)/build/libmlx42.a
INCLUDES := -I$(LIBFT_DIR) -I$(MLX42_DIR)/include -Iincludes -I/usr/include
LIBS := -lglfw -ldl -lm -pthread
SRCS_DIR := srcs
OBJS_DIR := build

# Para probar en otro entorno ⚠️ Borrar al final
BREW_PREFIX := /opt/homebrew
INCLUDES := -I$(LIBFT_DIR) -I$(MLX42_DIR)/include -Iincludes -I$(BREW_PREFIX)/include
LIBS := -L$(BREW_PREFIX)/lib -lglfw -ldl -lm -pthread

# Source files - Add new .c files here
SRCS = \
	$(SRCS_DIR)/main.c \
	$(SRCS_DIR)/parser/utils.c \
	$(SRCS_DIR)/parser/check.c \
	$(SRCS_DIR)/parser/map.c \
	$(SRCS_DIR)/parser/textures.c \
	$(SRCS_DIR)/execution/init.c \
	$(SRCS_DIR)/execution/player.c \
	$(SRCS_DIR)/execution/render.c \
	$(SRCS_DIR)/execution/game_loop.c \
	$(GNL_DIR)/get_next_line_bonus.c \
	$(GNL_DIR)/get_next_line_utils_bonus.c \

OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

BLUE = \033[0;34m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re debug banner libft

all: $(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJS)
	@clear
	@echo "$(GREEN)"
	@echo "\t ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ "
	@echo "\t██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗"
	@echo "\t██║     ██║   ██║██████╔╝ █████╔╝██║  ██║"
	@echo "\t██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║"
	@echo "\t╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝"
	@echo "\t ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ "
	@echo "                                               "
	@echo "$(BLUE)                🚀 42 School Project 🚀 "
	@echo "$(RED)                  juan-jof & lginer-m     "
	@echo "$(RESET)"
	@echo "$(GREEN)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✅ Built $(NAME)$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)📙 Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX42):
	@echo "$(YELLOW)🖼️  Building MLX42...$(RESET)"
	@cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR)
	@make -C $(MLX42_DIR)/build

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔧 Compiling $< -> $@$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@) #Crea las subcarpetas necesarias
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(BLUE)🧹 Object files cleaned!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean || true
	@rm -rf $(MLX42_DIR)/build || true
	@echo "$(RED)🔥 $(NAME) has been deleted!$(RESET)"

re: fclean all

debug: CFLAGS += -g -O0 -fsanitize=address,undefined
debug: all