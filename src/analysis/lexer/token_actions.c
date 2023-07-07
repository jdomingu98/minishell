#include "minishell.h"

void	transist(t_lex_state *current_state, char ch_read)
{
	if ((current_state == L_QUOTE && ch_read == '\'')
		|| (current_state == L_DQUOTE && ch_read == '"')
		|| (current_state == L_INIT && !ft_strchr("<' |\">", ch_read)))
		*current_state = L_STRING;
	else if ((current_state == L_INIT && ch_read == '\'')
		|| (current_state == L_STRING && ch_read == '\''))
		*current_state = L_QUOTE;
	else if ((current_state == L_INIT && ch_read == '"')
		|| (current_state == L_STRING && ch_read == '"'))
		*current_state = L_DQUOTE;
	else if ((current_state == L_STRING && ft_strchr("< |>", ch_read)))
		*current_state = L_INIT;
}

void	apppend_lexer_token(t_list **tokens, char *cmd) //???
{
	t_token_data	*last_token;
	char			*substr;
	char			*aux;

	last_token = ft_lstlast(*tokens)->content;
	substr = ft_substr(cmd, 0, 1);
	aux = ft_strjoin(last_token->value, substr);
	free(substr);
	free(last_token->value);
	last_token->value = aux;
}

t_list	*new_lexer_token(t_token token_type, char *value)
{
	t_token_data	*new;

	new = ft_calloc(1, sizeof(t_token_data));
	new->token = token_type;
	new->name = ft_strdup("");
	new->value = value;
	return (ft_lstnew(new));
}

void	free_lexer_token_data(void *token)
{
	t_token_data	*tmp;

	if (!token)
		return ;
	tmp = (t_token *) token;
	if (tmp->value)
		free(tmp->value);
	if (tmp->name)
		free(tmp->name);
	free(tmp);
}