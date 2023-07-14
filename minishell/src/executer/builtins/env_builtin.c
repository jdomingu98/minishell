/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:27:57 by atrujill          #+#    #+#             */
/*   Updated: 2023/07/14 01:27:59 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
