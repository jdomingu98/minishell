
#include "minishell.h"

static char	**realloc_export_env_vars(t_data *data, int len)
{
	char	**upt_export_env;
	int		i;

	i = 0;
	upt_export_env= ft_calloc(len + 1, sizeof * upt_export_env);
	if (!upt_export_env)
		return (0);
	while (data->exportenv[i] && i < len)
	{
		upt_export_env[i] = ft_strdup(data->exportenv[i]);
		free_ptr(data->exportenv[i]);
		i++;
	}
	free(data->exportenv);
	return (upt_export_env);
}

int	set_export_env_var(t_data *data, char *key, char *value)
{
	int		index;
	char	*aux;

	index = get_env_var_index(data->exportenv, key);
	if (!value)
		value = "";
	aux = ft_strjoin("=", value);
	if (!aux)
		return (12);
	if (index != -1 && data->exportenv[index])
	{
		free_ptr(data->exportenv[index]);
		data->exportenv[index] = ft_strjoin(key, aux);
	}
	else
	{
		index = env_size(data->exportenv);
		data->exportenv = realloc_export_env_vars(data, index + 1);
		if (!data->exportenv)
			return (12);
		data->exportenv[index] = ft_strjoin(key, aux);
	}
	free_ptr(aux);
	return (0);
}
