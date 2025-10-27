NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCDIR = .
LEXER_DIR = lexer
PARSER_DIR = parser
EXPANDER_DIR = expander
EXECUTOR_DIR = executor
BUILTINS_DIR = builtins
ERROR_DIR = error
UTILS_DIR = utils

SRCS = main.c \
	lexer/lexer_main.c lexer/lexer_split.c lexer/lexer_tokens.c lexer/lexer_utils.c \
	parser/parser_main.c parser/parser_utils.c \
	expander/expander_main.c \
	executor/executor_main.c executor/executor_utils.c executor/executor_redirections.c executor/executor_pipeline.c executor/executor_single.c executor/executor_utils2.c \
	builtins/builtin_echo.c builtins/builtin_pwd.c builtins/builtin_env.c builtins/builtin_exit.c builtins/builtin_cd.c builtins/builtin_export.c builtins/builtin_unset.c \
	utils/env_utils.c utils/env_array_utils.c utils/node_utils.c utils/string_utils.c \
	error/error_handler.c \
	signals.c

OBJS = $(SRCS:.c=.o)

LIBS = -lreadline $(LIBFT)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
