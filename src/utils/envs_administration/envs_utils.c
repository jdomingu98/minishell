/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:25:06 by jdomingu          #+#    #+#             */
/*   Updated: 2023/07/14 01:25:09 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_environments(t_data *data)
{
	free_env_copy(data->env, calc_env_size(data->env));
	free_env_copy(data->export_env, calc_env_size(data->export_env));
	free(data->env);
	free(data->export_env);
}

/**
 * @description: frees the env copy variable until last_index index 
 * @param env: The environment copy.
 * @param last_index: Last index to free the env copy.
 * @return: nothing.
*/
void	free_env_copy(char **env, int last_index)
{
	int	i;

	i = -1;
	while (++i < last_index)
		free(env[i]);
}

/**
 * @description: Calculates the number of rows that the env variable has
 * @param env: The original environment variable.
 * @return: A number with the row length of the env variable.
*/
size_t	calc_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/**
 * @description: Generates a copy of the envp variable.
 * @param env: The original environment variable.
 * @return: A copy of the env passed by parameter
*/
char	**copy_env(char **env)
{
	int		i;
	char	**env_copy;

	i = 0;
	env_copy = ft_calloc(calc_env_size(env) + 1, sizeof(char *));
	if (!env_copy)
		return (NULL);
	while (env[i])
	{
		env_copy[i] = ft_strdup(env[i]);
		if (!(env_copy[i]))
			return (free_env_copy(env_copy, i), NULL);
		i++;
	}
	return (env_copy);
}
