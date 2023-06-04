NAME	= minishell
CFLAGS	= -Wall -Wextra -Werror 
LIBFT	= libft
HEADERS = -I $(LIBFT) -I ./includes -I /Users/${USER}/.brew/opt/readline/include
LIBS 	= $(LIBFT)/libft.a
SOURCES = src

FILES	= minishell.c signals.c
SRCS	= $(addprefix $(SOURCES)/, $(FILES))
OBJS	= $(SRCS:.c=.o)

all:	libft $(NAME)

libft:	
	make -C $(LIBFT)

%.o: %.c
	gcc $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(SRCS) $(LIBFT)/libft.a -lreadline -L /Users/${USER}/.brew/opt/read-line/lib $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)/libft.a

re: fclean all

.PHONY: all clean fclean re libft