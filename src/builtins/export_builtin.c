
#include "minishell.h"

void	free_split(char **arg)
{
	int	i;

	i = 0;
	//if (!arg)
	//	return ;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

static int	is_valid_key(char *arg)
{
	char	**valid_key;
	char	*invalid_arg;
	int		i;
	int		code_number;

	i = 0;
	code_number = 1;
	invalid_arg = ":-!/?+^.,";
	if (arg[0] == '=')
		return (0);
	valid_key = ft_split(arg, '=');
	while (((i < (int)ft_strlen(valid_key[0]))) && (code_number == 1))
	{
		if (ft_strchr(invalid_arg, valid_key[0][i])
			|| ft_isdigit(valid_key[0][0]))
			code_number = 0;
		i++;
	}
	free_split(valid_key);
	return (result);
}

static int	set_vars(t_command *cmd, t_data *data)
{
	int		i;
	char	**args;
	char	**export_line;

	i = 0;
	args = cmd->args;
	while (++i < cmd->args)
	{
		if (is_valid_key(args[i]))
		{
			if (!ft_strchr(args[i], '='))
				set_export_env_var(data, args[i], "");
			else
			{
				 export_line = ft_split(args[i], '=');
				add_env_var(data, export_line[0], export_line[1]);
				set_export_env_var(data, export_line[0], export_line[1]);
				free_split(export_line);
			}
		}
		else
			return (print_error("export", args[i], "not a valid identifier",
					1));
	}
	return (0);
}

int	export_builtin(t_command *cmd, t_data *data)
{
	char	**export_line;
	int		code_number;
	int		i;

	code_number = 0;
	if (cmd->ac == 1)
	{
		i = 0;
		while ((data->export_env)[i])
		{
			export_line = ft_split(data->export_env[i], '=');
			if (!export_line[1])
				printf("declare -x %s\n", export_line[0]);
			else
				printf("declare -x %s=\"%s\"\n", export_line[0], export_line[1]);
			free_split(export_line);
			i++;
		}
	}
	else if (cmd->ac > 1)
		code_number = set_vars(cmd, data);
	return (code_number);
}
