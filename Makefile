NAME = pipex

# Source files (root directory files only)
SRC = pipex.c \
      pipex_utils.c

# Object files (in obj directory)
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0
# -fsanitize=address -fsanitize=leak -g

# Libft configuration
LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Include directories
INCLUDES = -I. -I$(LIBFT_DIR)

# Default target
all: $(NAME)

# Build libft first
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Build the main executable
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

# Compile object files
$(OBJ_DIR)/%.o: %.c pipex.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJ_DIR)/*.o
	@make clean -C $(LIBFT_DIR)

# Clean everything
fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
