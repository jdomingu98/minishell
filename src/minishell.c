#include "minishell.h"

/**
 * With the input read generates a list of token (the result of a lexer analysis).
 * With the list of tokens generates the data of the command list (the result of a parser analysis).
 * @param input_line: The input that had been read earlier
 * @param data: The data structure
 * @return The commads list to be executed
*/
static t_list	*get_command_list(char *input_line, t_data *data)
{
	t_list	*tokens_list;
	t_list	*commands_list;

	if (!input_line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		close_shell(data, g_status.status_code);
	}
	expand_variables(&input_line, data, false);
	tokens_list = lexer_analysis(input_line);
	if (!tokens_list)
		return (NULL);
	commands_list = parser_analysis(tokens_list, data);
	ft_lstclear(&tokens_list, &free_lexer_token_data);
	return (commands_list);
}

/**
 * Initialized the data structure and fill part of it with the env copies and with the duplicates of stdin and stdout.
 * @param env: The original env variable
 * @return The data structure stored in memory and with the env copies and with the stdin/stdout duplicates added.
*/
static t_data	*init_data(char **env)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = copy_env(env);
	if (!(data->env))
		return (free(data), NULL);
	data->export_env = copy_env(env);
	if (!(data->export_env))
		return (free(data->env), free(data), NULL);
	data->stdin_dup = dup(STDIN_FILENO);
	data->stdout_dup = dup(STDOUT_FILENO);
	return (data);
}

/**
 * The main function. Reads the command input, adds it to the history and call the functions to analyze and parse the command.
 * Then, the command list is executed.
 * @param argc: Argument counter
 * @param argv: List of arguments
 * @param envp: Environment path
 * @return Zero if all gone fine, other result if something gone wrong
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
		input = readline("MiniShell% > ");
		add_history(input);
		set_non_interactive_signals();
		data->command_list = get_command_list(input, data);
		free(input);
		if (!data->command_list)
			continue ;
		if (ft_lstsize(data->command_list) == 1)
			g_status.status_code = execute_input(data); //
		else if (ft_lstsize(data->command_list) > 1)
			g_status.status_code = execute_with_pipe(data); //
		free_command_list(&(data->command_list));
	}
	return (EXIT_SUCCESS);
}
