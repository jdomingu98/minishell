#include "minishell.h"

int	env_builtin(t_command *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (cmd->ac > 1)
		return (print_error("env", NULL, "too many arguments", 2));
	while ((data->env)[i])
	{
		ft_putendl_fd((data->env)[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
