CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./includes/libft

NAME = minishell

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -lreadline -L$(LIBFT_DIR) -lft

BUILTIN_DIR = builtin
EXECUTOR_DIR = executor
LEXER_DIR = lexer
PARSER_DIR = parser
UTILS_DIR = utils


BUILTIN_SRCS = $(BUILTIN_DIR)/cd.c $(BUILTIN_DIR)/echo.c $(BUILTIN_DIR)/env_operations.c \
               $(BUILTIN_DIR)/error.c $(BUILTIN_DIR)/exit.c $(BUILTIN_DIR)/export.c \
               $(BUILTIN_DIR)/pwd.c $(BUILTIN_DIR)/unset.c

EXECUTOR_SRCS = $(EXECUTOR_DIR)/command_execution.c

LEXER_SRCS = $(LEXER_DIR)/lexer_args.c $(LEXER_DIR)/lexer_cluster.c \
             $(LEXER_DIR)/lexer_files.c $(LEXER_DIR)/lexer_free.c \
             $(LEXER_DIR)/lexer_heredoc.c $(LEXER_DIR)/lexer_open.c

PARSER_SRCS = $(PARSER_DIR)/parser_chars.c $(PARSER_DIR)/parser_clean.c \
              $(PARSER_DIR)/parser_variables.c $(PARSER_DIR)/parser_dollar_expand.c \
              $(PARSER_DIR)/parser_env.c  $(PARSER_DIR)/parser_quotes.c \
              $(PARSER_DIR)/parser_free.c $(PARSER_DIR)/parser_len.c \
              $(PARSER_DIR)/parser_main.c $(PARSER_DIR)/parser_tilde.c \
              $(PARSER_DIR)/parser_nodes.c $(PARSER_DIR)/parser_pipes.c \
              $(PARSER_DIR)/parser_input_redirect.c $(PARSER_DIR)/parser_output_redirect.c \
              
UTILS_SRCS = $(UTILS_DIR)/get_env.c $(UTILS_DIR)/route_builtin_dispatcher.c \
			 $(UTILS_DIR)/memory_cleanup.c $(UTILS_DIR)/error_handling.c \
			 $(UTILS_DIR)/process_management.c $(UTILS_DIR)/parser_env_utils.c \
			 $(UTILS_DIR)/parser_utils.c $(UTILS_DIR)/parser_quotes_utils.c \
			 $(UTILS_DIR)/get_next_line.c $(UTILS_DIR)/signal.c \

SRCS = main.c $(BUILTIN_SRCS) $(EXECUTOR_SRCS) \
       $(LEXER_SRCS) $(PARSER_SRCS) $(UTILS_SRCS)

OBJS = $(SRCS:.c=.o)

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