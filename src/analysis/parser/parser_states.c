#include "minishell.h"

t_error	init_state(t_list *tokens, t_pars_state *state, t_list **commands)
{
	t_token_data	*token_data;

	token_data = (t_token_data *) tokens->content;
	*state = pars_next_state(*state, token_data);
	if (token_data->token == T_STRING)
		return (pars_append_new_command(commands, token_data->value));
	if (token_data->token == T_REDIR_IN)
		return (pars_append_new_command(commands, 0));
	if (token_data->token == T_REDIR_OUT)
		return (pars_append_new_command(commands, 0));
	if (token_data->token == T_APPEND)
		return (pars_append_new_command(commands, 0));
	if (token_data->token == T_HEREDOC)
		return (pars_append_new_command(commands, 0));
	if (token_data->token == T_PIPE)
		return (SYNTAX);
	return (NO_ERROR);
}

t_error	command_state(t_list *tokens, t_pars_state *state, t_list **commands)
{
	t_token_data	*token_data;

	token_data = (t_token_data *) tokens->content;
	*state = pars_next_state(*state, token_data);
	if (token_data->token == T_STRING)
		return (pars_append_arg_to_command(*commands, token_data->value));
	return (NO_ERROR);
}

t_error	redir_in_state(t_list *tokens, t_pars_state *state, t_list **commands)
{
	t_token_data	*token_data;

	token_data = (t_token_data *) tokens->content;
	*state = pars_next_state(*state, token_data);
	if (token_data->token == T_STRING)
		return (pars_set_stdin(*commands, token_data->value));
	if (token_data->token == T_PIPE)
		return (SYNTAX);
	return (NO_ERROR);
}

t_error	redir_out_state(t_list *tokens, t_pars_state *state, t_list **cmds)
{
	t_token_data	*token_data;

	token_data = (t_token_data *) tokens->content;
	*state = pars_next_state(*state, token_data);
	if (token_data->token == T_STRING)
		return (pars_set_stdout(*cmds, token_data->value, 0));
	if (token_data->token == T_PIPE)
		return (SYNTAX);
	return (NO_ERROR);
}

t_error	append_state(t_list *tokens, t_pars_state *state, t_list **cmds)
{
	t_token_data	*token_data;

	token_data = (t_token_data *) tokens->content;
	*state = pars_next_state(*state, token_data);
	if (token_data->token == T_STRING)
		return (pars_set_stdout(*cmds, token_data->value, 1));
	if (token_data->token == T_PIPE)
		return (SYNTAX);
	return (NO_ERROR);
}