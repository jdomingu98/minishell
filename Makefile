NAME	 = minishell
LIBFT	 = libft
# =================================================================================
CFLAGS	 = -Wall -Wextra -Werror 
HEADERS  = -I $(LIBFT) -I ./includes -I /Users/${USER}/.brew/opt/readline/include
LIBS 	 = $(LIBFT)/libft.a -lreadline -L /Users/${USER}/.brew/opt/read-line/lib
# =================================================================================
SRC_DIR  = src
BUILTINS_DIR = $(SRC_DIR)/builtins
# =================================================================================
FILES	 = minishell.c signals.c
SRCS	 = $(addprefix $(SRC_DIR)/, $(FILES))
OBJS	 = $(SRCS:.c=.o)
# =================================================================================

all:	 libft $(NAME)

%.o:	 %.c
	 gcc $(CFLAGS) $(HEADERS) -c $< -o $@

libft:
	 make -C $(LIBFT)

$(NAME): $(OBJS)
	 gcc $(CFLAGS) $(SRCS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBFT)
	rm -rf $(NAME)

re: fclean all

.PHONY: all libft clean fclean re
