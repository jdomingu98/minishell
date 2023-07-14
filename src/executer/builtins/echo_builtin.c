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

static void	print_echo_string(char **args, int nflag, int i)
{
	if (!args[i] && !nflag)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !nflag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int	echo_builtin(char **args)
{
	int		i;
	bool	flag;

	flag = check_if_n_flag(args[1]);
	i = 1;
	while (args[i] && flag)
	{
		i++;
		flag = check_if_n_flag(args[i]);
	}
	print_echo_string(args, flag, i);
	return (1);
}
