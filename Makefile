
NAME		= minishell
CFLAGS 		= -Wall -Wextra -Werror
NORMFLAG	= -R CheckForbiddenSourceHeader
SRC_DIR		= src
LIBFT_DIR	= libft
HEADERS		= -I $(LIBFT_DIR)
FILES		= minishell.c
SRCS		= $(addprefix $(SRC_DIR)/, $(FILES))
OBJS		= $(SRCS:.c=.o)

all:		libft $(NAME)

libft:
				make -C $(LIBFT_DIR)

$(NAME):	$(OBJS)
				gcc $(CFLAGS) $(SRCS) $(LIBFT_DIR)/libft.a $(HEADERS) -o $(NAME)

%.o:		%.c
				gcc $(CFLAGS) -c $< -o $@

clean:
				rm -f $(OBJS)

fclean:		clean
				rm -f $(NAME)

re:			fclean all

norm:
				norminette $(NORMFLAG) src

.PHONY:		all clean fclean re norm libft