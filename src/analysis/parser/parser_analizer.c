#include "minishell.h"

//set_pipes

static void	pars_print_error(t_pars_state current_state, t_error error_type)
{
	if (error_type == MALLOC)
		print_error("parser", 0, "memory error", 0);
	else if (error_type == NOT_FOUND)
		print_error("parser", 0, "no such file or directory", 0);
	else if (current_state != P_COMMAND || error_type == SYNTAX)
		print_error("parser", 0, "syntax error", 0);
}

t_error	error_states(t_list *tokens, t_pars_state *current,
		t_list **cmd_list, t_data *data)
{
	t_error	error;

	error = SYNTAX;
	if (*current == P_INIT)
		error = init_state(tokens, current, cmd_list);
	else if (*current == P_COMMAND)
		error = command_state(tokens, current, cmd_list);
	else if (*current == P_REDIR_IN)
		error = redir_in_state(tokens, current, cmd_list);
	else if (*current == P_REDIR_OUT)
		error = redir_out_state(tokens, current, cmd_list);
	else if (*current == P_APPEND)
		error = append_state(tokens, current, cmd_list);
	else if (*current == P_HEREDOC)
		error = heredoc_state(tokens, current, cmd_list, data);
	else if (*current == P_INVALID)
		error = invalid_state(tokens, current);
	return (error);
}

t_list	*parser_analysis(t_list *tokens, t_data *data)
{
	t_list			*cmd_list;
	t_pars_state	current_state;
	t_error			error_type;

	cmd_list = NULL;
	current_state = P_INIT;
	error_type = NO_ERROR;
	while (tokens && error_type == NO_ERROR)
	{
		error_type = error_states(tokens, &current_state, &cmd_list, data);
		tokens = tokens->next;
	}
	pars_print_error(current_state, error_type);
	if (error_type != NO_ERROR || current_state != P_COMMAND)
		return (free_command_list(&cmd_list), NULL);
	set_pipes(cmd_list);
	return (cmd_list);
}
