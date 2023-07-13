#include "minishell.h"

static void	set_pipes(t_list *cmd_list)
{
	t_command	*current_cmd;
	t_command	*next_cmd;
	int			fds[2];

	while (cmd_list)
	{
		current_cmd = (t_command *) cmd_list->content;
		if (cmd_list->next)
		{
			next_cmd = (t_command *) cmd_list->next->content;
			pipe(fds);
			if (current_cmd->out_fileno == 0)
				ft_memcpy(&(current_cmd->out_fileno), fds + 1, sizeof(int));
			else
				close(fds[1]);
			if (next_cmd->in_fileno == 0)
				ft_memcpy(&(next_cmd->in_fileno), fds + 0, sizeof(int));
			else
				close(fds[0]);
		}
		cmd_list = cmd_list->next;
	}
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
		error = redir_out_append_state(tokens, current, cmd_list, false);
	else if (*current == P_APPEND)
		error = redir_out_append_state(tokens, current, cmd_list, true);
	else if (*current == P_HEREDOC)
		error = heredoc_state(tokens, current, cmd_list, data);
	else if (*current == P_INVALID)
		transist_parser(current, ((t_token_data *) tokens->content)->token);
	return (error);
}

void	transist_parser(t_pars_state *current_state, t_token token)
{
	if (*current_state == P_COMMAND && token == T_PIPE)
		*current_state = P_INIT;
	else if ((*current_state == P_INIT && token == T_PIPE)
		|| ((*current_state == P_REDIR_IN || *current_state == P_HEREDOC
				|| *current_state == P_REDIR_OUT || *current_state == P_APPEND)
			&& token != T_STRING))
		*current_state = P_INVALID;
	else if ((*current_state != P_COMMAND && *current_state != P_INVALID)
		&& token == T_STRING)
		*current_state = P_COMMAND;
	else if ((*current_state == P_INIT || *current_state == P_COMMAND)
		&& token == T_REDIR_IN)
		*current_state = P_REDIR_IN;
	else if ((*current_state == P_INIT || *current_state == P_COMMAND)
		&& token == T_HEREDOC)
		*current_state = P_HEREDOC;
	else if ((*current_state == P_INIT || *current_state == P_COMMAND)
		&& token == T_REDIR_OUT)
		*current_state = P_REDIR_OUT;
	else if ((*current_state == P_INIT || *current_state == P_COMMAND)
		&& token == T_APPEND)
		*current_state = P_APPEND;
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
	if (error_type == MALLOC)
		print_error("parser", 0, "memory error", 0);
	else if (error_type == NOT_FOUND)
		print_error("parser", 0, "no such file or directory", 0);
	else if (current_state != P_COMMAND || error_type == SYNTAX)
		print_error("parser", 0, "syntax error", 0);
	if (error_type != NO_ERROR || current_state != P_COMMAND)
		return (free_command_list(&cmd_list), NULL);
	set_pipes(cmd_list);
	return (cmd_list);
}
