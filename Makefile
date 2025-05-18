NAME = pipex

SRC = src/main.c \
      src/utils2.c

OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
    @make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
    $(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
    $(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -c $< -o $@

clean:
    rm -f $(OBJ)

fclean: clean
    rm -f $(NAME)
    make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
