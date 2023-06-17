#include "minishell.h"

void free_data_envs(t_data *data, int i, bool is_export_env)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		free(data->env[j]);
		free(data->env_export[j]);
	}
	if (is_export_env)
		free(data->env[j]);
}

static size_t	get_env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

static void	init_environment(t_data *data, char **env)
{
	int i;

	i = -1;
	data->env = ft_calloc(get_env_size(env) + 1, sizeof(char **));
	data->env_export = ft_calloc(get_env_size(env) + 1, sizeof(char **));
	if (!data->env || !data->env_export)
		return ;
	while(env[++i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
		{
			free_data_envs(data, i, false);
			return ;
		}
		data->env_export[i] = ft_strdup(env[i]);
		if (!data->export_env[i])
		{
			free_data_envs(data, i, true);
			return ;
		}
	}
}

static t_data	*init_data(char **envp)
{
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	init_environment(data, envp);
	return (data);
}

/**
 * @description: The main function
 * @param argc: Argument counter
 * @param argv: List of arguments
 * @param envp: Environment path
 * @return: 0
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*input;

	(void) argc;
	(void) argv;
	data = init_data(envp);
	while (42)
	{
		set_interactive_signals();
		line = readline("MiniShellAny% > ");
		add_history(line);
		set_non_interactive_signals();
		//data->command_list = analyze_line(&line, data);
		free(line);

	}
	return (0);
}