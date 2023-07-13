/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:28:29 by atrujill          #+#    #+#             */
/*   Updated: 2023/07/14 01:28:31 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			delete_line_env(data->env, i_env);
		if (i_exp != -1)
			delete_line_env(data->export_env, i_exp);
		i++;
	}
	return (0);
}

int	unset_builtin(t_command *cmd, t_data *data)
{
	int	code_number;

	code_number = 0;
	if (cmd->ac > 1)
		code_number = unset_env_vars(cmd, data);
	return (code_number);
}
