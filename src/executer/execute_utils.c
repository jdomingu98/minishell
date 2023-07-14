/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:27:24 by atrujill          #+#    #+#             */
/*   Updated: 2023/07/14 01:31:18 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	decode_exit_code(int num)
{
	int	code_number;

	code_number = 1;
	if (WIFEXITED(num))
		code_number = WEXITSTATUS(num);
	return (code_number);
}

int	execute_builtins(t_command *cmd, t_data *data)
{
	int	status;

	status = 0;
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		status = echo_builtin(cmd->args);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		status = env_builtin(cmd, data);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		status = exit_builtin(cmd, data);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		status = export_builtin(cmd, data);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		status = unset_builtin(cmd, data);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		status = cd_builtin(cmd, data);
	return (status);
}

bool	is_builtin(char *cmd)
{
	return (ft_strncmp(cmd, "echo", 5) == 0
		|| ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "cd", 3) == 0);
}
