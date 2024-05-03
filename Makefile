# Compiler
CC = cc

# Compilation flags
CFLAGS = -g -Wall -Wextra -Werror 

# Source files for PIPEX
PIPEX_SRCS = src/pipex.c src/pipex_utils.c
				 

# Object files for push_swap
PIPEX_OBJS = $(PIPEX_SRCS:%.c=%.o)			

# Object files for checker
CHECKER_OBJS = $(CHECKER_SRCS:%.c=%.o)

# Library name
LIBFT_NAME = libft.a

# Path to libft
LIBFT_DIR = libft

# Flags for library inclusion
LIBFT_INC = -I$(LIBFT_DIR)
LIBFT_LINK = -L$(LIBFT_DIR) -lft

# Name of the PIPEX executable
PIPEX_NAME = pipex

all: $(PIPEX_NAME)

# Rule to build the PIPEX executable
$(PIPEX_NAME): $(PIPEX_OBJS) $(LIBFT_DIR)/$(LIBFT_NAME) 
	$(CC) $(CFLAGS) $(LIBFT_INC) $^ -o $@


# Rule to build object files for PIPEX
%.o: %.c
	$(CC) $(CFLAGS) $(LIBFT_INC) -c $< -o $@

# Rule to build libft
$(LIBFT_DIR)/$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_DIR)

# Rule to clean object files for both PIPEX and checker
clean:
	rm -f $(PIPEX_OBJS) 
	$(MAKE) -C $(LIBFT_DIR) clean

# Rule to clean object files and executables for both PIPEX and checker
fclean: clean
	rm -f $(PIPEX_NAME) 
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rule to recompile everything
re: fclean all





.PHONY: all clean fclean re libft bonus
