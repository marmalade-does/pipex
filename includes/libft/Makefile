NAME = libft.a

# Mandatory libft functions
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
       ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
       ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
       ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
       ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
       ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
       ft_tolower.c ft_toupper.c

# Bonus functions
BONUS_SRCS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
             ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
             ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

# ft_printf functions (included as part of this libft)
PRINTF_SRCS = ft_printf.c print_hexptry.c print_types.c

# All sources combined for default compilation
ALL_SRCS = $(SRCS) $(PRINTF_SRCS)

# Object files
OBJS = $(ALL_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Headers
HEADERS = libft.h ft_printf.h

# Default target
all: $(NAME)

# Create the library with mandatory and printf functions
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Bonus rule - adds bonus functions to existing library
bonus: $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

# Compile object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS) $(BONUS_OBJS)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

# Phony targets
.PHONY: all bonus clean fclean re