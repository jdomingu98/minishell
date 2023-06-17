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

	+ libft functions
*/

/* ================================================= GLOBAL VARIABLES ================================================= */

/**
 * @name: g_status_code
 * @description:
 * 		Contains the latest status code of the command executed.
 * 		Used as a return value in the command "$?".
*/
int	g_status_code;

/* ============================================= STRUCTURES AND ENUMERATIONS =========================================== */

/**
 * @name: enum t_lex_state
 * @description: Enumerates the states of the lexer state machine. see first diagram in README.md
 * 		@state: INIT
 * 		@description: Initial state
 * 		
 * 		@state: STRING
 * 		@description: A character string
 * 		
 * 		@state: QUOTE
 * 		@description: A simple quote (')
 *  
 * 		@state: VARIABLE
 * 		@description: TBA
 *  	
 * 		@state: DQUOTE
 * 		@description: A double quote (")
 *  
 *  	@state: VARIABLE_DQUOTE
 * 		@descirption: TBA
*/
typedef enum e_lex_state
{
	INIT, //LEX_START
	STRING, // LEX_WORD
	QUOTE, //LEX_SIMPLE_QUOTE
	VARIABLE, //LEX_VAR
	DQUOTE, //LEX_DOUBLE_QUOTE
	VARIABLE_DQUOTE //LEX_VAR_DOUBLE_QUOTE
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
 * 		@descirption: The symbol '|'
*/
typedef enum e_token
{
	STRING, //TOK_WORD
	REDIR_IN, //REDIR_IN
	REDIR_OUT, //TOK_REDIR_OUT
	APPEND, // TOK_REDIR_OUT_APPEND
	HEREDOC, //TOK_HDOC
	PIPE //TOK_PIPE
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
 * 		@description: TBA
 * 		
 * 		@state: REDIR_IN
 * 		@description: TBA
 *  
 * 		@state: REDIR_OUT
 * 		@description: TBA
 *  	
 * 		@state: APPEND
 * 		@description: TBA
 *  
 *  	@state: HEREDOC
 * 		@descirption: TBA
 * 	
 * 		@state: INVALID
 * 		@descirption: Invalid state. Will show an error.
*/
typedef enum e_pars_state
{
	INIT, //PARS_START
	COMMAND, //PARS_COMMAND
	REDIR_IN, //PARS_REDIR_IN
	REDIR_OUT, //PARS_REDIR_OUT
	APPEND, //PARS_REDIR_OUT_APPEND
	HEREDOC, //PARS_REDIR_IN_HEREDOC
	INVALID //PARS_INVALID
}	t_pars_state; //t_pars_st

/**
 * @name: enum t_error
 * @description: Enumerates the types of error that will occur while parsing the command
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
 * @name: struct t_key
 * @description: Stores the key data of the struct t_dictionary
 * 		@var: name
 * 		@description: The variable name
 * 		
 * 		@var: only_in_export
 * 		@description:
 * 			TRUE if the variable is only present in the export builtin
 * 			FALSE if is presente in both envs
*/
typedef struct s_key
{
	char	*name;
	bool	only_in_export;
}	t_key;

/**
 * @name: struct t_dictionary
 * @description: Stores the environment data using a dictionary data structure
 * 		@var: t_key key
 * 		@description: The unique key of the dictionary
 * 		
 * 		@var: value
 * 		@description: The value of the key
*/
typedef struct s_dictionary
{
	t_key	key;
	char	*value;
}	t_dictionary;

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
 * 		@description: Copy of the envp variable of the main function as a dictionary data structure.
 * 		
 * 		@var: t_list commands
 * 		@description:
 * 			List of read commands.
 * 			The type t_list is located in libft.h
 * 			The attribute "void *content" of the t_list struct is now casting to a "t_command* content" attribute.
 *  
 * 		@var: dup_stdin
 * 		@description: TBA
 * 	
 * 		@var: dup_stdout
 * 		@description: TBA
*/
typedef struct s_data
{
	t_list		*env;
	t_list		*command_list; //commands
	int			dup_stdin;
	int			dup_stdout;
}	t_data;

/* ===================================================== FUNCTIONS ==================================================== */

/* ========================================= BASE DIRECTORY ======================================= */

void	set_interactive_signals(void);
void	set_non_interactive_signals(void);

/* ============================================ BUILTINS ========================================== */


#endif