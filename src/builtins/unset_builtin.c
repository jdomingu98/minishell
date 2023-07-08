#include "minishell.h"

static int	unset_env_vars(t_command *cmd, t_data *data)
{
	char	**args;
	int		i;
	int		i_exp;
	int		i_env;

	i = 1;
	args = cmd->args;
	while (i < cmd->ac)
	{
		i_env = get_env_index(data->env, args[i]);
		i_exp = get_env_index(data->export_env, args[i]);
		if (i_env == -1 || i_exp == -1)
			return (print_error("unset", args[i], "var does not exist", 1));
		if (i_env != -1)
			delete_env_var(data, i_env);
		if (i_exp != -1)
			delete_export_var(data, i_exp);
		i++;
	}
	return (0);
}

int	unset_builtin(t_command *cmd, t_data *data)
{
	int	code_number;

	code_number = 0;
	if (cmd->ac > 1)
		code_number = unset_vars(cmd, data);
	return (code_number);
}
