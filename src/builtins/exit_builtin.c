
#include "minishell.h"

void	close_shell(t_data *data, int code_number)
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
	exit(code_number);
}

static int	is_number(char *str)
{
	int	i;
	int	code_number;

	i = 0;
	code_number = 1;
	if (!str)
		return (0);
	while (str[i] && code_number)
	{
		code_number = ft_isdigit(str[i]);
		i++;
	}
	return (code_number);
}

int	exit_builtin(t_command *cmd, t_data *data)
{
	int	code_number;

	ft_printf("exit\n");
	if (cmd->ac > 2)
	{
		if (!is_number(cmd->args[1]))
			close_shell(data,
				print_error("exit", 0, "numeric argument required", 255));
		return (print_error("exit", 0, "too many arguments", 1));
	}
	if (!is_number(cmd->args[1]) && cmd->args > 1)
		close_shell(data,
			print_error("exit", 0, "numeric argument required", 255));
	else if (cmd->args == 1)
		close_shell(data, 0);
	else
	{
		code_number = ft_atoi(cmd->args[1]) % 256;
		close_shell(data, code_number);
	}
	return (255);
}
