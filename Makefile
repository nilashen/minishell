NAME = minishell

SRC_BUILTIN = cd.c echo.c env.c error.c exit.c export.c pwd.c unset.c
SRC_ERROR = error_utils.c error_utils_2.c
SRC_EXEC = exec.c exec_utils.c
SRC_GNL = get_next_line.c
SRC_LEXER = lexer_cluster.c lexer_args.c lexer_files.c lexer_free.c \
			lexer_heredoc.c lexer_open.c
SRC_PARSER = parser_main.c parser_utils.c parser_clean.c parser_free.c \
			 parser_len.c parser_nodes.c parser_chars.c parser_pipes.c \
			 parser_env.c parser_env_utils.c parser_tilde.c \
			 parser_quotes.c parser_quotes_utils.c parser_redirect_in.c \
             parser_redirect_out.c parser_dollar.c parser_dollar_expand.c
SRC_UTILS = get_env.c route.c signal.c

SRCS = minishell.c \
	$(addprefix builtin/,$(SRC_BUILTIN)) \
	$(addprefix error/,$(SRC_ERROR)) \
	$(addprefix executor/,$(SRC_EXEC)) \
	$(addprefix gnl/,$(SRC_GNL)) \
	$(addprefix lexer/,$(SRC_LEXER)) \
	$(addprefix parser/,$(SRC_PARSER)) \
	$(addprefix utils/,$(SRC_UTILS))

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes -I $(LIBFT_DIR)
LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
