
NAME	 = minishell
LIBFT	 = libft
# =================================================================================

CFLAGS	 = -Wall -Wextra -Werror #-g -fsanitize=address
HEADERS  = -I $(LIBFT) -I /Users/${USER}/.brew/opt/readline/include -I src
LIBS 	 = $(LIBFT)/libft.a -lreadline -L /Users/${USER}/.brew/opt/readline/lib
# =================================================================================

SRC_DIR  = src/
LEXER_DIR = src/analysis/lexer/
PARSER_DIR = src/analysis/parser/
BUILTINS_DIR = src/builtins/
UTILS_DIR = src/utils/
ENV_UTILS = src/env_utils/
# =================================================================================

LEXER_FILES = lexer_states.c token_actions.c
LEXER_SRCS = $(addprefix $(LEXER_DIR), $(LEXER_FILES))

UTILS_FILES = signals.c env_utils.c
UTILS_SRCS = $(addprefix $(UTILS_DIR), $(UTILS_FILES))

ENV_UTILS_FILES = delete_env_var.c delete_export_var.c get_env_value.c \
					set_export_env_vars.c split_env.c
ENV_UTILS_SRCS = $(addprefix $(ENV_UTILS), $(ENV_UTILS_FILES))

BUILTINS_FILES = cd_builtin.c echo_builtin.c env_builtin.c exit_builtin.c \
					export_builtin.c pwd_builtin.c unset_builtin.c
BUILTINS_SRCS = $(addprefix $(BUILTINS_DIR), $(BUILTINS_FILES))

FILES	 = minishell.c
SRCS	 = $(addprefix $(SRC_DIR), $(FILES)) $(UTILS_SRCS) $(LEXER_SRCS) \
			$(BUILTINS_SRCS) $(ENV_UTILS_SRCS)

OBJS	 = $(SRCS:.c=.o)
# =================================================================================

all:	 libft $(NAME)

%.o:	 %.c
	gcc $(CFLAGS) $(HEADERS) -c $< -o $@

libft:
	make bonus -C $(LIBFT)

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
