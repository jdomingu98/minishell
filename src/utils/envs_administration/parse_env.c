/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrujill <atrujill@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:29:57 by atrujill          #+#    #+#             */
/*   Updated: 2023/07/14 01:30:37 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

static char	**process_path(char *arg)
{
	char	*aux;
	char	**result;
	int		i;

	i = 0;
	result = ft_split(arg, ':');
	if (!result)
		return (0);
	while (result[i])
	{
		aux = ft_strjoin(result[i], "/");
		free(result[i]);
		result[i] = aux;
		i++;
	}
	return (result);
}

char	**get_path(char **env)
{
	char	**result;
	char	**args;

	while (env)
	{
		args = ft_split(*env, '=');
		if (!args || !args[0] || !args[1])
			return (free_split(args), NULL);
		if (ft_strncmp(args[0], "PATH", 4) == 0)
		{
			result = process_path(args[1]);
			free_split(args);
			return (result);
		}
		else
			free_split(args);
		env++;
	}
	return (0);
}
