#include "minishell.h"

t_error	heredoc_state(t_list *tokens, t_pars_state *state, t_list **cmds, t_data *data)
{
	t_token_data	*token_data;

	token_data = (t_token_data *) tokens->content;
	*state = pars_next_state(*state, (t_token *) tokens->content);
	if (token_data->token == T_STRING)
		return (pars_create_heredoc(*cmds, token_data->value, data));
	if (token_data->token == T_PIPE)
		return (SYNTAX);
	return (NO_ERROR);
}

t_error	invalid_state(t_list *tokens, t_pars_state *state)
{
	*state = pars_next_state(*state, (t_token *) tokens->content);
	return (SYNTAX);
}