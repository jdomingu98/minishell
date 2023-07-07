#ifndef MINISHELL_H
# define MINISHELL_H

/* ===================================================== LIBRARIES ==================================================== */

# include <stdio.h> //readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, perror
# include <readline/readline.h> //readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <readline/history.h> //readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <fcntl.h> //open
# include <sys/types.h> //fork, wait, waitpid, wait3, wait4, lstat, fstat, opendir, closedir
# include <sys/wait.h> //wait, waitpid, wait3, wait4
# include <sys/time.h> //wait3, wait4
# include <sys/resource.h> //wait3, wait4
# include <signal.h> //signal, sigaction, kill
# include <sys/stat.h> //stat, lstat, fstat
# include <dirent.h> //opendir, readdir, closedir
# include <string.h> //strerror
# include <errno.h> //perror
# include <sys/ioctl.h> //ioctl
# include <termios.h> //tcgetattr, tcgetattr
# include <curses.h> //tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs (routines)
# include <term.h> //tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs (routines)
// https://man7.org/linux/man-pages/man3/curs_termcap.3x.html

# include <limits.h> // MAX_INT, MIN_INT
# include <stdbool.h> // bool type

# include "libft.h"
/*
    unistd: write, access, read, close, fork, getcwd, chdir, lstat,
            fstat, unlink, execve, dup, dup2, pipe, isatty, ttyname,
            ttyslot, tcgetattr, tcgetattr
    stdlib: malloc, free, exit, getenv, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO
	libft functions
*/

/* ================================================= GLOBAL VARIABLES ================================================= */

/**
 * @name: struct t_g_state
 * @description: Stores the data of the command state.
 * 		@var: status_code
 * 		@description: Last status command exit code.
 * 		
 * 		@var: process_id
 * 		@description: Process id of the current command executed.
*/
typedef struct s_g_state
{
	int		status_code;
	pid_t	process_id;
}	t_g_state;

/**
 *	@name: t_g_state status
 *	@description: A global variable to be used for setting the last status code. Is used in the command "$?"
 */
extern t_g_state status;

/* ============================================= STRUCTURES AND ENUMERATIONS =========================================== */

/**
 * @name: enum t_lex_state
 * Enumerates the states of the lexer state machine. see first diagram in README.md
 * 		@state: INIT
 * 		@description: Initial state
 * 		
 * 		@state: STRING
 * 		@description: A character string
 * 		
 * 		@state: QUOTE
 * 		@description: A simple quote (')
 *  	
 * 		@state: DQUOTE
 * 		@description: A double quote (")
*/
typedef enum e_lex_state
{
	L_INIT, //LEX_START
	L_STRING, // LEX_WORD
	L_QUOTE, //LEX_SIMPLE_QUOTE
	L_DQUOTE //LEX_DOUBLE_QUOTE
}	t_lex_state; //t_lex_st

/**
 * @name: enum t_token
 * @description: Enumerates the possible tokens. The election depends of the final state of the lexer
 * 		@value: STRING
 * 		@description: A char string
 * 		
 * 		@value: REDIR_IN
 * 		@description: The symbol '>'
 * 		
 * 		@value: REDIR_OUT
 * 		@description: The symbol '<'
 *  
 * 		@value: APPEND
 * 		@description: The symbol '>>'
 *  	
 * 		@value: HEREDOC
 * 		@description: The symbol '<<'
 *  
 *  	@value: PIPE
 * 		@description: The symbol '|'
*/
typedef enum e_token
{
	T_STRING, //TOK_WORD
	T_REDIR_IN, //REDIR_IN
	T_REDIR_OUT, //TOK_REDIR_OUT
	T_APPEND, // TOK_REDIR_OUT_APPEND
	T_HEREDOC, //TOK_HDOC
	T_PIPE //TOK_PIPE
}	t_token; //t_token_type

/**
 * @name: struct t_token_data
 * @description: Stores the data related to one token
 * 		@var: name
 * 		@description: The variable name
 * 		
 * 		@var: value
 * 		@description: The variable value
 * 		
 * 		@var: t_token token
 * 		@description: The e_token enum value
*/
typedef struct s_token_data
{
	char	*name; //var_name
	char	*value;
	t_token	token; //type
}			t_token_data; //t_token

/**
 * @name: enum t_pars_state
 * @description: Enumerates the states of the parser state machine. See second diagram in README.md
 * 		@state: INIT
 * 		@description: Initial state
 * 		
 * 		@state: COMMAND
 * 		@description: Command. Is stored in data->commands.
 * 		
 * 		@state: REDIR_IN
 * 		@description: IN redirection
 *  
 * 		@state: REDIR_OUT
 * 		@description: OUT redirection
 *  	
 * 		@state: APPEND
 * 		@description: Append state
 *  
 *  	@state: HEREDOC
 * 		@description: Heredoc state.
 * 	
 * 		@state: INVALID
 * 		@description: Invalid state. Will show an error.
*/
typedef enum e_pars_state
{
	P_INIT, //PARS_START
	P_COMMAND, //PARS_COMMAND
	P_REDIR_IN, //PARS_REDIR_IN
	P_REDIR_OUT, //PARS_REDIR_OUT
	P_APPEND, //PARS_REDIR_OUT_APPEND
	P_HEREDOC, //PARS_REDIR_IN_HEREDOC
	P_INVALID //PARS_INVALID
}	t_pars_state; //t_pars_st

/**
 * @name: enum t_error
 * @description: Enumerates the types of error that will occur while parsing the command. All the parser states return a t_error value.
 * 		@value: SYNTAX
 * 		@description: Syntax Error
 * 		
 * 		@value: MALLOC
 * 		@description: Memory Allocation Error
 * 		
 * 		@value: NOT_FOUND
 * 		@description: A word that can be a directory o a file doesn't exist
 *  
 * 		@value: NO_ERROR
 * 		@description: No error occurred
*/
typedef enum e_error
{
	SYNTAX, //PARS_SYNTAX_ERROR
	MALLOC, // PARS_MALLOC_ERROR
	NOT_FOUND, //PARS_NO_SUCH_FILE_OR_DIR
	NO_ERROR //PARS_NO_ERROR
}	t_error; //t_pars_err

/**
 * @name: struct t_command
 * @description: Stores the data of the command launched by the user
 * 		@var: ac
 * 		@description: Argument counter of the command read
 * 		
 * 		@var: args
 * 		@description: List of arguments of the read command
 * 		
 * 		@var: in_fileno
 * 		@description: Input file descriptor number
 * 
 * 		@var: out_fileno
 * 		@description: Output file descriptor number
*/
typedef struct	s_command
{
    int		ac; //argc
	char	**args; //argv
	int		in_fileno; //fd_in
	int		out_fileno; //fd_out
}			t_command;

/**
 * @name: struct t_data
 * @description: Stores all useful data used during the execution of the minishell.
 * 		@var: env
 * 		@description: Copy of the envp variable of the main function.
 * 
 * 		@var: env_export
 * 		@description: Copy of the envp variable of the main function. Used in export builtin
 * 		
 * 		@var: t_list commands
 * 		@description:
 * 			List of read commands.
 * 			The type t_list is located in libft.h
 * 			The attribute "void *content" of the t_list struct is now casting to a "t_command* content" attribute.
 *
 * 		@var: dup_stdin
 * 		@description: Duplicate of STDIN_FILENO. Needed for redirection.
 * 	
 * 		@var: dup_stdout
 * 		@description: Duplicate of STDOUT_FILENO. Needed for redirection.
*/
typedef struct s_data
{
	char		**env;
	t_list		*command_list; //commands
	char		**export_env;
	int			stdin_dup;
	int			stdout_dup;
}	t_data;

/* ==================================================== FUNCTIONS ==================================================== */

/* ========================================== SIGNALS ========================================== */

void	set_interactive_signals(void);
void	set_non_interactive_signals(void);

/* ========================================== ENV_UTILS ========================================== */

char	**copy_env(char** env);
size_t	calc_env_size(char **env);
void	free_env_copy(char **env, int last_index);
int		delete_env_var(t_data *data, int index);
int		add_env_var(t_data *data, char *key, char *value);
int		get_env_index(char **env, char *var);
int		delete_export_var(t_data *data, int index);
char	*get_env_value(t_data *data, char *key);
int		set_export_env_var(t_data *data, char *key, char *value);
char	**split_env(char *str);

/* ========================================== LEXER ========================================== */

t_list	*lexer_analysis(char *input);
void	transist(t_lex_state *current_state, char ch_read);
void	apppend_lexer_token(t_list **tokens, char *cmd);
void	free_lexer_token_data(void *token);
t_list	*new_lexer_token(t_token token_type, char *value);

/* ========================================== PARSER ========================================== */

t_list  *parser_analysis(t_list *tokens_list, t_data *data);

/* ========================================== BUILTINS ========================================== */
int	echo_builtin(char **args);
int	cd_builtin(t_command *cmd, t_data *data);
int	env_builtin(t_command *cmd, t_data *data);
int	exit_builtin(t_command *cmd, t_data *data);
int	export_builtin(t_command *cmd, t_data *data);
int	pwd_builtin(void);
int	unset_builtin(t_command *cmd, t_data *data);

#endif