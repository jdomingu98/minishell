
#include "minishell.h"

int	get_env_index(char **env, char *var)
{
	int		i;
	char	*aux;

	i = 0;
	aux = ft_strjoin(var, "=");
	if (!aux)
		return (-1);
	while (env[i])
	{
		if (ft_strncmp(aux, env[i], ft_strlen(aux)) == 0)
		{
			free_ptr(aux);
			return (i);
		}
		i++;
	}
	free_ptr(aux);
	return (-1);
}

static char	**realloc_env_vars(t_data *data, int len)
{
	char	**upt_env;
	int		i;

	i = 0;
	upt_env = ft_calloc(len + 1, sizeof(upt_env));
	if (!upt_env)
		return (0);
	while (data->env[i] && i < len)
	{
		upt_env[i] = ft_strdup(data->env[i]);
		free_ptr(data->env[i]);
		i++;
	}
	free(data->env);
	return (upt_env);
}

int	add_env_var(t_data *data, char *key, char *value)
{
	int		index;
	char	*aux;

	index = get_env_index(data->env, key);
	if (value == NULL)
		value = "";
	aux = ft_strjoin("=", value);
	if (!aux)
		return (12);
	if (index != -1 && data->env[index])
	{
		free_ptr(data->env[index]);
		data->env[index] = ft_strjoin(key, aux);
	}
	else
	{
		index = env_size(data->env);
		data->env = realloc_env_vars(data, index + 1);
		if (!data->env)
			return (12);
		data->env[index] = ft_strjoin(key, aux);
	}
	free_ptr(aux);
	return (0);
}

int	delete_env_var(t_data *data, int index)
{
	int	i;
	int	count;

	i = index;
	count = index;
	if (index > env_size(data->env))
		return (0);
	free_ptr(data->env[index]);
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_ptr(data->env[i + 1]);
		count++;
		i++;
	}
	data->env = realloc_env_vars(data, count);
	if (!data->env)
		return (0);
	return (1);
}
