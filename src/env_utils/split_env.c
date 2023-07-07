

#include "minishell.h"

char	**split_env(char *str)
{
	int		delimiter;
	int		i;
	char	**ptr_key_value;

	delimiter= 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			delimiter = i;
			break ;
		}
	}
	if (delimiter == 0)
		return (0);
	ptr_key_value = (char **)ft_calloc(3, sizeof(char *));
	if (!ptr_key_value)
		return (0);
	ptr_key_value[0] = ft_substr(str, 0, delimiter);
	ptr_key_value[1] = ft_substr(str, delimiter + 1, ft_strlen(str));
	return (ptr_key_value);
}
