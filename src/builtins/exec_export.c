
#include "minishell.h"

/* free_args:
* free the memory of export arguments.
*/
static void	free_args(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

/* print_export_env:
* put the key and the value in the export.
*/

static void	print_export_env(t_shell_data *data)
{
	char	**aux;
	int		i;
	char	**key_and_value;

	aux = data->exportenv;
	i = 0;
	while (i < env_size(aux))
	{
		key_and_value = ft_split(aux[i], '=');
		if (!key_and_value[1])
			printf("declare -x %s\n", key_and_value[0]);
		else
			printf("declare -x %s=\"%s\"\n", key_and_value[0], key_and_value[1]);
		free_args(key_and_value);
		i++;
	}
}

/* is_valid_key:
* verifies that the characters in the key are valid.
* returns 1 if error and returns 0 if correct.
*/

static int	is_valid_key(char *arg)
{
	char	**valid_key;
	char	*invalid_arg;
	int		i;
	int		result;

	i = 0;
	result = 1;
	invalid_arg = ":-!/?+^.,";
	if (arg[0] == '=')
		return (0);
	valid_key = ft_split(arg, '=');
	while (((i < (int)ft_strlen(valid_key[0]))) && (result == 1))
	{
		if (ft_strchr(invalid_arg, valid_key[0][i])
			|| ft_isdigit(valid_key[0][0]))
			result = 0;
		i++;
	}
	free_args(valid_key);
	return (result);
}

/* set_vars:
* "key" is equal to the name of the variables.
* "value" is equal to the content of the variables.
* if it is only the key and without the "=" it is only saved in the export.
* if it is the key with the "=" it is saved in the env and the export with empty string.
* if this both the key and the value is saved in env and export.
*/
static int	set_vars(t_command *command, t_shell_data *data)
{
	int		i;
	char	**args;
	char	**key_and_value;

	i = 0;
	args = command->argv;
	while (++i < command->argc)
	{
		if (is_valid_key(args[i]))
		{
			if (!ft_strchr(args[i], '='))
				set_export_env_var(data, args[i], "");
			else
			{
				key_and_value = ft_split(args[i], '=');
				set_env_var(data, key_and_value[0], key_and_value[1]);
				set_export_env_var(data, key_and_value[0], key_and_value[1]);
				free_args(key_and_value);
			}
		}
		else
			return (print_error("export", args[i], "not a valid identifier",
					1));
	}
	return (0);
}
/* built_in_export:
*checks to add one or more variables and reproduces the export function.
*/
int	built_in_export(t_command *command, t_shell_data *data)
{
	int	result;

	result = 0;
	if (command->argc == 1)
		print_export_env(data);
	else if (command->argc > 1)
		result = set_vars(command, data);
	return (result);
}
