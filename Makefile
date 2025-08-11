# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nashena <nashena@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/11 19:30:00 by nashena           #+#    #+#              #
#    Updated: 2025/08/11 20:03:24 by nashena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I. -I./library

# Libraries
LIBUTILS_DIR = ./library
LIBUTILS = $(LIBUTILS_DIR)/libutils.a

# System libraries (for readline, termcap, etc.)
LIBS = -lreadline -ltermcap

# Source files
SRCS = main.c \
       buildin.c \
       execution.c \
       path_finding_utils.c \
       redirections.c \
       utils_of_env.c

# Object files
OBJS = $(SRCS:.c=.o)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

# Default target
all: $(NAME)

# Build the program
$(NAME): $(LIBUTILS) $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBUTILS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

# Build the library
$(LIBUTILS):
	@echo "$(BLUE)Building libutils...$(RESET)"
	@make -C $(LIBUTILS_DIR)

# Compile source files
%.o: %.c minishell.h
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@make -C $(LIBUTILS_DIR) clean

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBUTILS_DIR) fclean

# Rebuild everything
re: fclean all

# Run the program
run: $(NAME)
	@echo "$(GREEN)Running $(NAME)...$(RESET)"
	@./$(NAME)

# Debug mode
debug: CFLAGS += -fsanitize=address -fsanitize=undefined
debug: $(NAME)

# Check for memory leaks with valgrind
leaks: $(NAME)
	@echo "$(BLUE)Checking for memory leaks...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

# Install readline (if needed)
install-readline:
	@echo "$(BLUE)Installing readline...$(RESET)"
	@brew install readline || sudo apt-get install libreadline-dev

# Show help
help:
	@echo "$(GREEN)Available targets:$(RESET)"
	@echo "  all          - Build the program"
	@echo "  clean        - Remove object files"
	@echo "  fclean       - Remove all generated files"
	@echo "  re           - Rebuild everything"
	@echo "  run          - Build and run the program"
	@echo "  debug        - Build with debug flags"
	@echo "  leaks        - Check for memory leaks"
	@echo "  help         - Show this help message"

# Phony targets
.PHONY: all clean fclean re run debug leaks install-readline help