#include "minishell.h"

void	free_split(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	**split_env(char *str)
{
	char	**key_value;
	int		delimiter;
	int		i;

	delimiter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			delimiter = i;
			break ;
		}
		i++;
	}
	if (delimiter == 0)
		return (NULL);
	key_value = ft_calloc(3, sizeof(char *));
	if (!key_value)
		return (NULL);
	key_value[0] = ft_substr(str, 0, delimiter);
	key_value[1] = ft_substr(str, delimiter + 1, ft_strlen(str));
	return (key_value);
}
