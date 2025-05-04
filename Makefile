## this make file is total ass

NAME = pipex

SRC = src/main.c \
      src/utils2.c

OBJ = $(SRC:.c=.o)

CC = gcc
CCFLAGS = -Werror -Wall -Wextra

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
    @make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
    $src/(CC) $src/(CCFLAsrc/GS) $(src/OBJ) -src/L$(LIBsrc/FT_DIRsrc/) -lftsrc/ -o $(src/NAME)
src/
%.o: src/%.c
    $(CC) $(CCFLAGS) -Iincludes -I$(LIBFT_DIR) -c $< -o $@

clean:
    rm -f $(OBJ)

fclean: clean
    rm -f $(NAME)
    make fclean -C $(LIBFT_DIR)

re: fclean all

debug: $(LIBFT) $(OBJ)
    $(CC) $(CCFLAGS) -fsanitize=address $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

.PHONY: all clean fclean re debug