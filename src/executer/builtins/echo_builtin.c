/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:27:43 by atrujill          #+#    #+#             */
/*   Updated: 2023/07/14 01:27:45 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_if_n_flag(char *flag)
{
	int		i;

	if (ft_strncmp(flag, "-n", 2) != 0)
		return (false);
	i = 1;
	while (flag[i] && flag[i] == 'n')
		i++;
	return (!flag[i]);
}

static void	print_echo_string(char **args, int idx)
{
	while (args[idx])
	{
		if (!check_if_n_flag(args[idx]))
		{
			ft_putstr_fd(args[idx], STDOUT_FILENO);
			if (args[idx + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		idx++;
	}
}

int	echo_builtin(t_command *cmd)
{
	if (cmd->ac == 2 && check_if_n_flag(cmd->args[1]))
		return (0);
	if (cmd->ac == 1)
		ft_putendl_fd("", STDOUT_FILENO);
	else if (cmd->ac >= 2 && !check_if_n_flag(cmd->args[1]))
	{
		print_echo_string(cmd->args, 1);
		ft_putendl_fd("", STDOUT_FILENO);
	}
	else
		print_echo_string(cmd->args, 2);
	return (0);
}
