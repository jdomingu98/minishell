/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:36:54 by jdomingu          #+#    #+#             */
/*   Updated: 2023/07/13 17:36:54 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INFO: https://man7.org/linux/man-pages/man3/curs_termcap.3x.html

/* ============================= LIBRARIES ============================= */

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <limits.h>
# include <stdbool.h>
# include "libft.h"

/* ====================== STRUCTURES AND ENUMERATIONS ====================== */

typedef struct s_g_state
{
	int		status_code;
	pid_t	process_id;
}	t_g_state;

typedef enum e_lex_state
{
	L_INIT,
	L_STRING,
	L_QUOTE,
	L_DQUOTE
}	t_lex_state;

typedef enum e_token
{
	T_STRING,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_PIPE
}	t_token;

typedef struct s_token_data
{
	char	*name;
	char	*value;
	t_token	token;
}	t_token_data;

typedef enum e_pars_state
{
	P_INIT,
	P_COMMAND,
	P_REDIR_IN,
	P_REDIR_OUT,
	P_APPEND,
	P_HEREDOC,
	P_INVALID
}	t_pars_state;

typedef enum e_error
{
	SYNTAX,
	MALLOC,
	NOT_FOUND,
	NO_ERROR
}	t_error;

typedef struct s_command
{
	int		ac;
	char	**args;
	int		in_fileno;
	int		out_fileno;
}	t_command;

typedef struct s_data
{
	char		**env;
	t_list		*command_list;
	char		**export_env;
	int			stdin_dup;
	int			stdout_dup;
}	t_data;

/* ============================= FUNCTIONS ============================= */

/* ================== LEXER ================== */

t_list	*lexer_analysis(char *input);
void	transist(t_lex_state *current_state, char ch_read);
void	append_lexer_token(t_list **tokens, char *cmd);
void	free_lexer_token_data(void *token);
t_list	*new_lexer_token(t_token token_type, char *value);

/* ================== PARSER ================== */

t_list	*parser_analysis(t_list *tokens_list, t_data *data);
void	transist_parser(t_pars_state *current_state, t_token token);
t_error	error_states(t_list *tokens, t_pars_state *current,
			t_list **cmd_list, t_data *data);
t_error	init_state(t_list *tokens, t_pars_state *state, t_list **commands);
t_error	command_state(t_list *tokens, t_pars_state *state, t_list **commands);
t_error	redir_in_state(t_list *tokens, t_pars_state *state, t_list **commands);
t_error	redir_out_append_state(t_list *tokens, t_pars_state *state,
			t_list **cmds, bool is_append);
t_error	heredoc_state(t_list *tokens, t_pars_state *state,
			t_list **cmds, t_data *data);
t_error	set_stdin(t_list *cmd_list, char *fname);
t_error	set_stdout(t_list *cmd_list, char *fname, bool is_append);
t_error	append_command_arg(t_list *cmd_list, char *new_arg);
t_error	append_command(t_list **cmd_list, char *new_cmd);
void	free_command_list(t_list **command_list);
t_error	create_heredoc(t_list *cmd_list, char *token_value, t_data *data);

/* ================== EXECUTER ================== */

int		execute_input(t_list *in_str, t_data *data);
int		execute_with_pipe(t_data *data);
bool	is_builtin(char *cmd);
int		execute_builtins(t_command *cmd, t_data *data);
int		decode_exit_code(int num);

/* ============== BUILTINS ============== */

int		echo_builtin(char **args);
int		cd_builtin(t_command *cmd, t_data *data);
int		env_builtin(t_command *cmd, t_data *data);
int		exit_builtin(t_command *cmd, t_data *data);
void	close_shell(t_data *data, int code_number);

int		export_builtin(t_command *cmd, t_data *data);
int		pwd_builtin(void);
int		unset_builtin(t_command *cmd, t_data *data);

/* ======================== UTILS ======================== */

void	close_pipes(t_data *data, t_list *instr);
int		print_error(char *command, char *detail, char *error_message, int err);
char	*join_strs(char *str, char *add);
void	set_interactive_signals(void);
void	set_non_interactive_signals(void);
void	expand_variables(char **line, t_data *data, bool expand_quotes);

/* ============ ENV_ADMINISTRATION ============ */

char	**copy_env(char	**env);
size_t	calc_env_size(char **env);
void	free_env_copy(char **env, int last_index);
void	free_environments(t_data *data);
char	*get_env_value(t_data *data, char *key);
int		get_env_index(char **env, char *var);
int		add_to_env(char **env, char *key, char *value);
int		delete_line_env(char **env, int pos);
char	**split_env(char *str);
void	free_split(char **args);
char	**get_path(char **env);
void	free_path(char **path);

/* ============================ GLOBAL VARIABLE ============================ */

extern t_g_state	g_status;

#endif