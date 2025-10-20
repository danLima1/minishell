NAME = libftprintf.a

SRCS = ft_printf.c ft_printf_utils.c ft_putptr.c
OBJS = $(SRCS:.c=.o)

COMPILER = cc -Wall -Wextra -Werror

all: $(NAME)

.c.o:
	@ $(COMPILER) -c -I . $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
	@ ar rc $(NAME) $(OBJS)


re: fclean $(NAME)

exec: re
	@ $(COMPILER) main.c libftprintf.a -o exec
	@ clear
	@ ./exec

clean:
	@ rm -rf $(OBJS)

fclean: clean
	@ rm -rf $(NAME)

aclean: fclean
	@ rm -rf exec

.PHONY: all clean fclean re exec
