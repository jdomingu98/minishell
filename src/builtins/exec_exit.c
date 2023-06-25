
#include "minishell.h"

/* exitshell:
* free all and exit.
*/
void	exitshell(t_shell_data *data, int exitcode)
{
	if (data)
	{
		free_envs(data);
		ft_lstclear(&data->commands, del_t_command);
		if (data->dup_stdin)
			close(data->dup_stdin);
		if (data->dup_stdout)
			close(data->dup_stdout);
		free(data);
	}
	exit(exitcode);
}
/* is_num:
* checks is the strings is a strings of numbers.
*/
static int	is_num(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	if (!str)
		return (0);
	while (str[i] && result)
	{
		result = ft_isdigit(str[i]);
		i++;
	}
	return (result);
}
/* built_in_exit:
* checks if exit is possible and saves the output type.
*/
int	built_in_exit(t_command *command, t_shell_data *data)
{
	int	code;

	ft_printf("exit\n");
	if (command->argc > 2)
	{
		if (!is_num(command->argv[1]))
			exitshell(data,
				print_error("exit", 0, "numeric argument required", 255));
		return (print_error("exit", 0, "too many arguments", 1));
	}
	if (!is_num(command->argv[1]) && command->argc > 1)
		exitshell(data,
			print_error("exit", 0, "numeric argument required", 255));
	else if (command->argc == 1)
		exitshell(data, 0);
	else
	{
		code = ft_atoi(command->argv[1]) % 256;
		exitshell(data, code);
	}
	return (255);
}
