# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Output library name
NAME = libftprintf.a

# Source and object files
SRC = ft_printf.c functions.c print_nbr.c print_unsigned.c
OBJ = $(SRC:.c=.o)

# Default rule
all: $(NAME)

# Archive object files into a static library
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

# Compile .c to .o
%.o: %.c printf.h
	$(CC) $(CFLAGS) -c $< -o $@

# Remove object files
clean:
	rm -f $(OBJ)

# Remove object files and the binary
fclean: clean
	rm -f $(NAME)

# Full rebuild
re: fclean all

# Prevent make from running these as file targets
.PHONY: all clean fclean re
