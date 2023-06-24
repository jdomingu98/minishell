#include "minishell.h"

/**
 * @description: With the line read generates a list of token (lexer)
 * 		With the list of tokens generates the data of the command list (parser)
 * @param input_line: The input that had been read earlier
 * @param data: The data structure
 * @return: The data structure stored in memory and with the env copies added
*/
t_list	*get_command_list(char **input_line, t_data *data)
{

}


/**
 * @description: Initialized the data structure and fill part of it with the env copies.
 * @param env: The original env variable
 * @return: The data structure stored in memory and with the env copies added
*/
static t_data	*init_data(char **env)
{
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = copy_env(env);
	if (!(data->env))
		return(free(data), NULL);
	data->export_env = copy_env(env);
	if (!(data->export_env))
		return(free(data->env), free(data), NULL);
	return (data);
}

/**
 * @description: The main function.
 * 	Reads the command input, adds it to the history and call the functions to analyze and parse the command.
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
	if (!data)
		return (EXIT_FAILURE);
	while (42)
	{
		set_interactive_signals();
		input = readline("MiniShellAny% > ");
		add_history(input);
		set_non_interactive_signals();
		data->command_list = get_command_list(&input, data);
		free(input);
		if(!data->command_list)
			continue ;
		if (ft_lstsize(data->command_list) == 1)
			status.status_code = execute_input(data);//
		else if (ft_lstsize(data->command_list) > 1)
			status.status_code = execute_with_pipe(data); //
		//pars_free_command_list(&(data->command_list));
	}
	return (EXIT_SUCCESS);
}