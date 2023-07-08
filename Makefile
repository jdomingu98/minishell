
NAME	 = minishell
LIBFT	 = libft
# =================================================================================

CFLAGS	 = -Wall -Wextra -Werror #-g -fsanitize=address
HEADERS  = -I $(LIBFT) -I /Users/${USER}/.brew/opt/readline/include -I src
LIBS 	 = $(LIBFT)/libft.a -lreadline -L /Users/${USER}/.brew/opt/readline/lib
# =================================================================================

SRC_DIR  = src/
ANALYSIS_DIR = $(SRC_DIR)analysis
LEXER_DIR = $(ANALYSIS_DIR)/lexer/
PARSER_DIR = $(ANALYSIS_DIR)/parser/
BUILTINS_DIR = $(SRC_DIR)builtins/
UTILS_DIR = $(SRC_DIR)utils/
ENV_ADMIN = $(UTILS_DIR)/env_administration/
# =================================================================================

LEXER_FILES = lexer_states.c token_actions.c
LEXER_SRCS = $(addprefix $(LEXER_DIR), $(LEXER_FILES))

PARSER_FILES = parser_analizer.c parser_states.c parser_states_part2.c free_command_list.c \
				parser_actions.c
PARSER_SRCS = $(addprefix $(PARSER_DIR), $(PARSER_FILES))

ENV_ADMIN_FILES = envs_management.c envs_split.c envs_uitls.c
ENV_ADMIN_SRCS = $(addprefix $(ENV_ADMIN), $(ENV_ADMIN_FILES))

UTILS_FILES = signals.c variables_expansion.c
UTILS_SRCS = $(addprefix $(UTILS_DIR), $(UTILS_FILES)) $(ENV_ADMIN_FILES)

BUILTINS_FILES = cd_builtin.c echo_builtin.c env_builtin.c exit_builtin.c \
					export_builtin.c pwd_builtin.c unset_builtin.c
BUILTINS_SRCS = $(addprefix $(BUILTINS_DIR), $(BUILTINS_FILES))

FILES	 = minishell.c
SRCS	 = $(addprefix $(SRC_DIR), $(FILES)) $(LEXER_SRCS) $(PARSER_SRCS)\
			$(UTILS_SRCS) $(BUILTINS_SRCS)

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
