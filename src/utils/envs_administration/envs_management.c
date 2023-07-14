/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:24:47 by jdomingu          #+#    #+#             */
/*   Updated: 2023/07/14 09:28:23 by atrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_data *data, char *key)
{
	char	**args;
	char	*res;
	size_t	key_len;
	int		i;

	i = 0;
	key_len = ft_strlen(key);
	while (data->env[i])
	{
		args = split_env(data->env[i]);
		if (!args || !args[0] || !args[1])
			return (free_split(args), NULL);
		if (ft_strncmp(args[0], key, key_len) == 0)
		{
			res = ft_strdup(args[1]);
			free_split(args);
			return (res);
		}
		else
			free_split(args);
		i++;
	}
	return (NULL);
}

int	get_env_index(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
			break ;
		i++;
	}
	free(tmp);
	if (env[i])
		return (i);
	return (-1);
}

static char	**realloc_env(char ***env, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while ((*env)[i] && i < size)
	{
		new_env[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	free(*env);
	return (new_env);
}

int	add_to_env(char ***env, char *key, char *value)
{
	int		idx;
	char	*eq_value;

	idx = get_env_index(*env, key);
	if (!value)
		value = "";
	eq_value = ft_strjoin("=", value);
	if (!eq_value)
		return (12);
	if (idx != -1 && (*env)[idx])
	{
		free((*env)[idx]);
		(*env)[idx] = ft_strjoin(key, eq_value);
	}
	else
	{
		idx = calc_env_size(*env);
		*env = realloc_env(env, idx + 1);
		if (!(*env))
			return (12);
		(*env)[idx] = ft_strjoin(key, eq_value);
	}
	free(eq_value);
	return (0);
}

int	delete_line_env(char ***env, int pos)
{
	int	i;

	if ((size_t) pos > calc_env_size(*env))
		return (0);
	if ((*env)[pos])
		free((*env)[pos]);
	i = pos;
	while ((*env)[i + 1])
	{
		(*env)[i] = ft_strdup((*env)[i + 1]);
		free((*env)[i + 1]);
		i++;
	}
	*env = realloc_env(env, i);
	if (!(*env))
		return (0);
	return (1);
}
