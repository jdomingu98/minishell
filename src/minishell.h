#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, perror
# include <readline/readline.h> //readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <readline/history.h> //readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <fcntl.h> //open
# include <sys/types.h> //fork, wait, waitpid, wait3, wait4, lstat, fstat, opendir, closedir
# include <sys/wait.h> //wait, waitpid, wait3, wait4
//# include <sys/time.h> //wait3, wait4
//# include <sys/resource.h> //wait3, wait4
# include <signal.h> //signal, sigaction, kill
# include <sys/stat.h> //stat, lstat, fstat
//# include <dirent.h> //opendir, readdir, closedir
//# include <string.h> //strerror
# include <errno.h> //perror
//# include <sys/ioctl.h> //ioctl
//# include <termios.h> //tcgetattr, tcgetattr
//# include <curses.h> //tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs (routines)
//# include <term.h> //tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs (routines)
// https://man7.org/linux/man-pages/man3/curs_termcap.3x.html
# include <limits.h>
# include <stdbool.h>

# include "libft.h"
/*
    unistd: write, access, read, close, fork, getcwd, chdir, lstat,
            fstat, unlink, execve, dup, dup2, pipe, isatty, ttyname,
            ttyslot, tcgetattr, tcgetattr
    stdlib: malloc, free, exit, getenv
*/

extern int	g_last_status_code;

typedef struct	s_data
{
    char    *input;
}	t_data;

void	init_interactive_signals(void);


#endif