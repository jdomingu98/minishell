#include "minishell.h"

/**
 * @description: Specifies the handler of the ctrl+C signal while the minishell is interactive
 * @param signal: The signal number (not used)
 * @return: nothing.
*/
static void	new_prompt(int signal)
{
	(void) signal;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @description: Specifies the behaviour of the SIGQUIT and SIGINT while the minishell is interactive
 * @return: nothing.
*/
void	set_interactive_signals(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	ft_bzero(&sigint_act, sizeof(sigint_act));
	sigint_act.sa_handler = &new_prompt;
	sigaction(SIGINT, &sigint_act, NULL);
	ft_bzero(&sigquit_act, sizeof(sigquit_act));
	sigquit_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigquit_act, NULL);
}

/**
 * @description: Specifies the handler of the ctrl+C and ctrl+\ signals while the minishell is non interactive
 * @param signal: The signal number (not used)
 * @return: nothing.
*/
static void	print_line(int signal)
{
	(void) signal;
	rl_on_new_line();
}

/**
 * @description: Specifies the behaviour of the SIGQUIT and SIGINT while the minishell is non interactive
 * @return: nothing.
*/
void	set_non_interactive_signals(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &print_line;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
