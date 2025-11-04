NAME := cub3D
CC := cc
CFLAGS := -g -Wall -Werror -Wextra \
		#-fsanitize=address,undefined \
		#-Wunreachable-code -Ofast \

LIBFT_DIR := Libft
LIBFT := $(LIBFT_DIR)/libft.a
INCLUDES := -I$(LIBFT_DIR) -Iinc -I/usr/include
SRCS_DIR := src
OBJS_DIR := build

# Auto-discover source files
SRCS := $(shell find $(SRCS_DIR) -type f -name '*.c' 2>/dev/null)
OBJS := $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

BLUE = \033[0;34m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re debug banner libft

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
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
	@if [ -f $(NAME) ]; then \
		echo "$(YELLOW)🔄 Relinking $(NAME)... (executable already exists)$(RESET)"; \
	else \
		echo "$(GREEN)🔗 Linking $(NAME)...$(RESET)"; \
	fi
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✅ Built $(NAME)$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)📙 Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

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
	@echo "$(RED)🔥 $(NAME) has been deleted!$(RESET)"

re: fclean all

debug: CFLAGS += -g -O0 -fsanitize=address,undefined
debug: all