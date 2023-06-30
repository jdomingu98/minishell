#include "minishell.h"

void	apppend_lexer_token(t_list **tokens, char **command) //??
{
}

t_list	*new_lexer_token(t_token token_type, char *value)
{
	t_token_data	*new;

	new = ft_calloc(1, sizeof(t_token_data));
	new->token = token_type;
	new->name = ""; //ft_strdup(""); ??
	new->value = value;
	return (ft_lstnew(new));
}

void	free_lexer_token_data(void *token)
{
	t_token_data	*tmp;

	if (!token)
		return ;
	tmp = (t_token *) token;
	//if (tmp->value)
		free(tmp->value);
	//if (tmp->name)
	free(tmp->name);
	free(tmp);
}