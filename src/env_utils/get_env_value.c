
#include "minishell.h"

char	*get_env_value(t_data *data, char *key)
{
	char	**args;
	char	*res_line;
	size_t	key_len;
	int		i;

	i = 0;
	key_len = ft_strlen(key);
	while (data->env[i])
	{
		args = split_env(data->env[i]);
		if (!args || !args[0] || !args[1])
			return (free_split(args));
		if (ft_strncmp(args[0], key, key_len) == 0)
		{
			res_line = ft_strdup(args[1]);
			free_split(args);
			return (res_line);
		}
		else
			free_split(args);
		i++;
	}
	return (0);
}
