NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

# Directories
SRCDIR = src
INCDIR = includes
OBJDIR = obj

# Source files
SOURCES = main.c \
          prompt.c \
          parser.c \
          executor.c

# Object files
SRCS = $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

# Header files
HEADERS = $(INCDIR)/minishell.h

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(OBJDIR)
	@echo "Compiling $< with includes from $(INCDIR)..."
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)

re: fclean all

# Phony targets
.PHONY: all clean fclean re