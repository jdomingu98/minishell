#include "minishell.h"

t_error	init_state(t_list *tokens, t_pars_state *state, t_list **commands)
{
	t_token_data	*token_data;

	token_data = (t_token_data *) tokens->content;
	transist_parser(state, token_data->token);
	if (token_data->token == T_PIPE)
		return (SYNTAX);
	if (token_data->token == T_STRING)
		return (append_command(commands, token_data->value));
	return (append_command(commands, NULL));
}

t_error	command_state(t_list *tokens, t_pars_state *state, t_list **commands)
{
	t_token_data	*token_data;

	token_data = (t_token_data *) tokens->content;
	transist_parser(state, token_data->token);
	if (token_data->token == T_STRING)
		return (append_command_arg(*commands, token_data->value));
	return (NO_ERROR);
}

t_error	redir_in_state(t_list *tokens, t_pars_state *state, t_list **commands)
{
	t_token_data	*token_data;

	token_data = (t_token_data *) tokens->content;
	transist_parser(state, token_data->token);
	if (token_data->token == T_STRING)
		return (set_stdin(*commands, token_data->value));
	if (token_data->token == T_PIPE)
		return (SYNTAX);
	return (NO_ERROR);
}

t_error	redir_out_append_state(t_list *tokens, t_pars_state *state, t_list **cmds, bool is_append)
{
	t_token_data	*token_data;

	token_data = (t_token_data *) tokens->content;
	transist_parser(state, token_data->token);
	if (token_data->token == T_STRING)
		return (set_stdout(*cmds, token_data->value, is_append));
	if (token_data->token == T_PIPE)
		return (SYNTAX);
	return (NO_ERROR);
}

t_error	heredoc_state(t_list *tokens, t_pars_state *state, t_list **cmds, t_data *data)
{
	t_token_data	*token_data;

	token_data = (t_token_data *) tokens->content;
	transist_parser(state, token_data->token);
	if (token_data->token == T_STRING)
		return (create_heredoc(*cmds, token_data->value, data));
	if (token_data->token == T_PIPE)
		return (SYNTAX);
	return (NO_ERROR);
}