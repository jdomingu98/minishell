#include "minishell.h"

/*static void print_new_line(int signal)
{
    (void) signal;
    rl_on_new_line();
}

void    set_noninteractive_signals(void) //no se si hay que ponerlo
{
    struct sigaction    act;

    ft_bzero(&act, sizeof(act));
    act.sa_handler = &print_new_line;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);
}*/

static void reset_prompt(int signal)
{
    (void) signal;
    ft_putchar_fd('\n', 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();

}

void	set_interactive_signals(void)
{
    struct sigaction    sigint_act;
    struct sigaction    sigquit_act;

    ft_bzero(&sigint_act, sizeof(sigint_act));
    sigint_act.sa_handler = &reset_prompt;
    sigaction(SIGINT, &sigint_act, NULL);
    ft_bzero(&sigquit_act, sizeof(sigquit_act));
    sigquit_act.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sigquit_act, NULL);
}