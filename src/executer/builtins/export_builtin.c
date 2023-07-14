/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:28:14 by atrujill          #+#    #+#             */
/*   Updated: 2023/07/14 01:28:16 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_valid_key(char *arg)
{
	char	**key_value;
	size_t	i;
	bool	valid;

	if (arg[0] == '=')
		return (false);
	key_value = ft_split(arg, '=');
	i = 0;
	valid = true;
	while (valid && i < ft_strlen(key_value[0]))
	{
		if (ft_strchr("+-.,:/!?^", key_value[0][i])
			|| ft_isdigit(key_value[0][i]))
			valid = false;
		i++;
	}
	free_split(key_value);
	return (valid);
}

static int	add_vars_to_envs(t_data *data, t_command *cmd)
{
	int		i;
	char	**args;
	char	**export_line;

	i = 0;
	args = cmd->args;
	while (++i < cmd->ac)
	{
		if (check_valid_key(args[i]))
		{
			if (!ft_strchr(args[i], '='))
				add_to_env(data->export_env, args[i], "");
			else
			{
				export_line = split_env(args[i]);
				add_to_env(data->env, export_line[0], export_line[1]);
				add_to_env(data->export_env, export_line[0], export_line[1]);
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
		while (data->export_env[i])
		{
			export_line = split_env(data->export_env[i]);
			if (!export_line[1])
				printf("declare -x %s\n", export_line[0]);
			else
				printf("declare -x %s=\"%s\"\n", export_line[0], export_line[1]);
			free_split(export_line);
			i++;
		}
	}
	else if (cmd->ac > 1)
		code_number = add_vars_to_envs(data, cmd);
	return (code_number);
}
