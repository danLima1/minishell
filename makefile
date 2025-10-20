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
       signals.c \
       $(LEXER_DIR)/lexer_split.c \
       $(LEXER_DIR)/lexer_tokens.c \
       $(LEXER_DIR)/lexer_utils.c \
       $(LEXER_DIR)/lexer_main.c \
       $(PARSER_DIR)/parser_main.c \
       $(PARSER_DIR)/parser_utils.c \
       $(EXPANDER_DIR)/expander_main.c \
       $(EXECUTOR_DIR)/executor_main.c \
       $(BUILTINS_DIR)/builtin_echo.c \
       $(BUILTINS_DIR)/builtin_pwd.c \
       $(BUILTINS_DIR)/builtin_env.c \
       $(BUILTINS_DIR)/builtin_exit.c \
       $(ERROR_DIR)/error_handler.c \
       $(UTILS_DIR)/node_utils.c \
       $(UTILS_DIR)/env_utils.c \
       $(UTILS_DIR)/string_utils.c

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
