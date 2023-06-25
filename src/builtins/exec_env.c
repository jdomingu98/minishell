
#include "minishell.h"

/* env:
*checks for correct data entry and prints environment variables
*/
int	built_in_env(t_command *command, t_shell_data *data)
{
	int	i;
	char **aux;

	aux = data->env;
	i = 0;
	if ( command->argc > 1)
		return (print_error("env", NULL, "too many arguments", 2));
	if (!command->argc)
		return (1);
	while (aux[i])
	{
		printf("%s\n", aux[i]);
		i++;
	}
	return (0);
}

