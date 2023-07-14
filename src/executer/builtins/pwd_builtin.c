/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:28:21 by atrujill          #+#    #+#             */
/*   Updated: 2023/07/14 01:28:23 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(void)
{
	char	*cwd;
	int		code_number;

	code_number = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		code_number = 1;
		return (code_number);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (code_number);
}
