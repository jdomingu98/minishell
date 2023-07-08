#include "minishell.h"

/**
 * @param flag: the flag of echo
 * @return:
 * 		TRUE if the flag is "-n" (there can be more than one "n")
 * 		FALSE otherwise
*/
static bool	check_if_n_flag(char *flag)
{
	int		i;

	if (ft_strncmp(flag, "-n", 2) != 0)
		return (false);
	i = 1;
	while (flag[i] && flag[i] == 'n')
		i++;
	return (!flag[i]);
}

/**
 * @param args: 
 * @param n_flag:
 * @param i:
 * @description: Prints the string args[i]. A new line if "-n" flag is not set
 * @return: nothing
*/
static void	print_echo_string(char **args, int nflag, int i)
{
	if (!args[i] && !nflag)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !nflag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

/**
 * Executes the echo builtin command: prints the given strings
 * and adds a \n character or not depending on the -n option.
 * Returns 1 on completion.
 * @param args: Contains the echo command ¿?
 * @return: 1 ¿?
*/

int	echo_builtin(char **args)
{
	int		i;
	bool	flag;

	flag = check_if_n_flag(args[1]);
	i = 1;
	while (args[i] && flag)
	{
		i++;
		flag = check_if_n_flag(args[i]);
	}
	print_echo_string(args, flag, i);
	return (1);
}
