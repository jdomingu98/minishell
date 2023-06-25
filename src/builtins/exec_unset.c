
#include "minishell.h"

/* unset_vars:
* checks if the variable exists and if so eliminates it.
*/
static int	unset_vars(t_command *command, t_shell_data *data)
{
	char	**args;
	int		i;
	int		i_exp;
	int		i_env;

	i = 1;
	args = command->argv;
	while (i < command->argc)
	{
		i_env = get_env_var_index(data->env, args[i]);
		i_exp = get_env_var_index(data->exportenv, args[i]);
		if (i_env == -1 || i_exp == -1)
			return (print_error("unset", args[i], "var does not exist", 1));
		if (i_env != -1)
			remove_env_var(data, i_env);
		if (i_exp != -1)
			remove_exportenv_var(data, i_exp);
		i++;
	}
	return (0);
}

/* built_in_unset:
* checks if the data input is correct and reproduces the unset function.
*/

int	built_in_unset(t_command *command, t_shell_data *data)
{
	int	result;

	result = 0;
	if (command->argc == 1)
		;
	else if (command->argc > 1)
		result = unset_vars(command, data);
	return (result);
}
