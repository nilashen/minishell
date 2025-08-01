
# Library name
NAME = libutils.a

# Header file
HEADER = libutils.h

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar

# Source directories
LIBFT_DIR = libft
PRINTF_DIR = ft_printf
GNL_DIR = get_next_line

# libft source files
LIBFT_SRC = ft_isalpha \
			ft_isdigit \
			ft_isalnum \
			ft_isascii \
			ft_isprint \
			ft_strlen \
			ft_memset \
			ft_bzero \
			ft_memcpy \
			ft_memmove \
			ft_strlcpy \
			ft_strlcat \
			ft_toupper \
			ft_tolower \
			ft_strchr \
			ft_strrchr \
			ft_strncmp \
			ft_memchr \
			ft_memcmp \
			ft_strnstr \
			ft_atoi \
			ft_calloc \
			ft_strdup \
			ft_substr \
			ft_strjoin \
			ft_strtrim \
			ft_split \
			ft_itoa \
			ft_strmapi \
			ft_striteri \
			ft_putchar_fd \
			ft_putstr_fd \
			ft_putendl_fd \
			ft_putnbr_fd \
			ft_strcmp 

# ft_printf source files
PRINTF_SRC = ft_printf \
			 ft_putchar \
			 ft_putstr \
			 ft_print_num \
			 ft_print_hex \
			 ft_print_ptr \
			 ft_print_us

# get_next_line source files
GNL_SRC = get_next_line \
		  get_next_line_utils

# Create full paths for source files
LIBFT_SRCS = $(addsuffix .c, $(LIBFT_SRC))
PRINTF_SRCS = $(addsuffix .c, $(PRINTF_SRC))
GNL_SRCS = $(addsuffix .c, $(GNL_SRC))

# All source files
SRCS = $(LIBFT_SRCS) $(PRINTF_SRCS) $(GNL_SRCS)

# Object files
LIBFT_OBJS = $(addsuffix .o, $(LIBFT_SRC))
PRINTF_OBJS = $(addsuffix .o, $(PRINTF_SRC))
GNL_OBJS = $(addsuffix .o, $(GNL_SRC))

OBJS = $(LIBFT_OBJS) $(PRINTF_OBJS) $(GNL_OBJS)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NC = \033[0m # No Color

# Default target
all: $(NAME)

# Create the library
$(NAME): $(OBJS)
	@echo "$(BLUE)Creating library $(NAME)...$(NC)"
	@$(AR) rcs $@ $^
	@echo "$(GREEN)✓ Library $(NAME) created successfully!$(NC)"

# Compile object files
%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Create directories if they don't exist
$(LIBFT_DIR):
	@mkdir -p $(LIBFT_DIR)

$(PRINTF_DIR):
	@mkdir -p $(PRINTF_DIR)

$(GNL_DIR):
	@mkdir -p $(GNL_DIR)

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -f $(OBJS)
	@echo "$(GREEN)✓ Object files cleaned!$(NC)"

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning library...$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Library cleaned!$(NC)"

# Rebuild everything
re: fclean all

# Help target
help:
	@echo "$(BLUE)Available targets:$(NC)"
	@echo "  $(YELLOW)all$(NC)     - Build the library"
	@echo "  $(YELLOW)clean$(NC)   - Remove object files"
	@echo "  $(YELLOW)fclean$(NC)  - Remove object files and library"
	@echo "  $(YELLOW)re$(NC)      - Rebuild everything"
	@echo "  $(YELLOW)help$(NC)    - Show this help message"


.PHONY: all clean fclean re help structure