
#include "minishell.h"

/* n_flag:
* Checks whether an arg is an -n option flag.
* Returns true = 1 if the arg is some variation of -n, -nnnn, -nn, etc.
* Returns false = 0 if it contains anything other than - and n (ex. --n -nm -n42)
*/
static int	n_flag(char *arg)
{
	int		i;
	int	n_flag;

	n_flag = 0;
	i = 0;
	if (ft_strncmp(arg, "-n", 2) != 0)
		return (n_flag);
	i = 1;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (!arg[i])
		n_flag = 1;
	return (n_flag);
}

/* echo_print:
* Prints the given array of aruments to STDOUT.
*/
static void	echo_print(char **args, int n_flag, int i)
{
	if (!args[i] && !n_flag)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}

	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

/* built_in_echo:
* Executes the echo builtin command: prints the given strings
* and adds a \n character or not depending on the -n option.
* Returns 1 on completion.
*/

int	built_in_echo(t_command *command)
{
	int		i;
	int	flag;
	char **aux;

	aux = command->argv;
	flag = 0;
	i = 1;
	while (aux[i] && n_flag(aux[i]))
	{
		flag = 1;
		i++;
	}
	echo_print(aux, flag, i);
	return (1);
}
