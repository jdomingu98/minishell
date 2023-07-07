
#include "minishell.h"

static char	**realloc_export_vars(t_data *data, int len)
{
	char	**upt_export;
	int		i;

	i = 0;
	upt_export = ft_calloc(len + 1, sizeof(upt_export));
	if (!upt_export)
		return (0);
	while (data->exportenv[i] && i < len)
	{
		upt_export[i] = ft_strdup(data->exportenv[i]);
		free_ptr(data->exportenv[i]);
		i++;
	}
	free(data->exportenv);
	return (upt_export);
}


int	delete_export_var(t_data *data, int index)
{
	int	i;
	int	count;

	i = index;
	count = index
	if (index > env_size(data->exportenv))
		return (0);
	free_ptr(data->exportenv[index]);
	while (data->exportenv[i + 1])
	{
		data->exportenv[i] = ft_strdup(data->exportenv[i + 1]);
		free_ptr(data->exportenv[i + 1]);
		count++;
		i++;
	}
	data->exportenv = realloc_export_vars(data, count);
	if (!data->exportenv)
		return (0);
	return (1);
}
