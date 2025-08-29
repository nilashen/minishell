# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./includes/libft

# Executable name
NAME = minishell

# Libraries
LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -lreadline -L$(LIBFT_DIR) -lft

# Source directories
BUILTIN_DIR = builtin
ERROR_DIR = error
EXECUTOR_DIR = executor
GNL_DIR = gnl
LEXER_DIR = lexer
PARSER_DIR = parser
UTILS_DIR = utils


BUILTIN_SRCS = $(BUILTIN_DIR)/cd.c $(BUILTIN_DIR)/echo.c $(BUILTIN_DIR)/env.c \
               $(BUILTIN_DIR)/error.c $(BUILTIN_DIR)/exit.c $(BUILTIN_DIR)/export.c \
               $(BUILTIN_DIR)/pwd.c $(BUILTIN_DIR)/unset.c

ERROR_SRCS = $(ERROR_DIR)/error_utils.c $(ERROR_DIR)/error_utils_2.c

EXECUTOR_SRCS = $(EXECUTOR_DIR)/exec.c $(EXECUTOR_DIR)/exec_utils.c

GNL_SRCS = $(GNL_DIR)/get_next_line.c

LEXER_SRCS = $(LEXER_DIR)/lexer_args.c $(LEXER_DIR)/lexer_cluster.c \
             $(LEXER_DIR)/lexer_files.c $(LEXER_DIR)/lexer_free.c \
             $(LEXER_DIR)/lexer_heredoc.c $(LEXER_DIR)/lexer_open.c \
             $(LEXER_DIR)/lexer_args_utils.c

PARSER_SRCS = $(PARSER_DIR)/parser_chars.c $(PARSER_DIR)/parser_clean.c \
              $(PARSER_DIR)/parser_dollar.c $(PARSER_DIR)/parser_dollar_expand.c \
              $(PARSER_DIR)/parser_env.c $(PARSER_DIR)/parser_env_utils.c \
              $(PARSER_DIR)/parser_free.c $(PARSER_DIR)/parser_len.c \
              $(PARSER_DIR)/parser_main.c $(PARSER_DIR)/parser_nodes.c \
              $(PARSER_DIR)/parser_pipes.c $(PARSER_DIR)/parser_quotes.c \
              $(PARSER_DIR)/parser_quotes_utils.c $(PARSER_DIR)/parser_redirect_in.c \
              $(PARSER_DIR)/parser_redirect_out.c $(PARSER_DIR)/parser_tilde.c \
              $(PARSER_DIR)/parser_utils.c

UTILS_SRCS = $(UTILS_DIR)/get_env.c $(UTILS_DIR)/route.c $(UTILS_DIR)/signal.c

# All source files
SRCS = main.c $(BUILTIN_SRCS) $(ERROR_SRCS) $(EXECUTOR_SRCS) $(GNL_SRCS) \
       $(LEXER_SRCS) $(PARSER_SRCS) $(UTILS_SRCS)

# Object files
OBJS = $(SRCS:.c=.o)

# Rules
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
