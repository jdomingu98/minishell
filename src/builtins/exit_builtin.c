
#include "minishell.h"

void	close_shell(t_data *data, int code_number)
{
	if (data)
	{
		free_envs(data); //
		ft_lstclear(&data->command_list, del_t_command); //
		if (data->stdin_dup)
			close(data->stdin_dup);
		if (data->stdout_dup)
			close(data->stdout_dup);
		free(data);
	}
	exit(code_number);
}

static bool	check_if_number(char *str)
{
	int	i;
	int	valid;

	if (!str)
		return (false);
	i = 0;
	valid = true;
	while (valid && str[i])
	{
		if (!ft_isdigit(str[i]))
			valid = false;
		i++;
	}
	return (valid);
}

int	exit_builtin(t_command *cmd, t_data *data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->ac > 2)
	{
		if (!check_if_number(cmd->args[1]))
			close_shell(data,
				print_error("exit", 0, "numeric argument required", 255));
		return (print_error("exit", 0, "too many arguments", 1));
	}
	if (!check_if_number(cmd->args[1]) && cmd->args > 1)
		close_shell(data,
			print_error("exit", 0, "numeric argument required", 255));
	else if (cmd->args == 1)
		close_shell(data, 0);
	else
		close_shell(data, ft_atoi(cmd->args[1]) % 256);
	return (255);
}