#include "minishell.h"

//PROBAR FUNCIONAMIENTO

/**
 * @description: Adds a new variable to the environment.
 * @param key: The key of the dictionary element
 * @param value: The value of the dictionary element
 * @param env: The dictionary of the environment
 * @return: nothing.
*/
void	add_env_variable(t_key key, char *value, t_list **env)
{
	t_dictionary	*dict;
	t_list			*new;

	dict = ft_calloc(1, sizeof(t_dictionary));
	new = ft_calloc(1, sizeof(t_list));
	//if (!dict || !new)
		//free
	dict->key = key;
	dict->value = value;
	new->content = dict;
	new->next = NULL;
	ft_lstadd_back(env, new);
}

/**
 * @description: Search and return the key value of the key passed by parameter
 * @param key: The key to be searched
 * @param env: The dictionary of the environment where the key should be
 * @return: The key value if found, NULL otherwise
*/
char	*get_key_value(t_key key, t_list *env)
{
	t_list	*aux;
	char	*name;

	aux = env;
	dict = (t_dictionary *) aux->content;
	while (aux->next)
	{
		if (ft_strncmp(key.name, dict->key->name, ft_strlen(dict->key->name)) == 0
			&& (dict->key->only_in_export == key->only_in_export))
			return (dict->value);
		aux = aux -> next;
	}
	return (NULL);
}

/**
 * @description: Search the key element in the env.
 * @param key: The key to search
 * @param env: The dictionary of the environment where the key should be
 * @return:	The key-value node if found, NULL otherwise
*/
static t_list	*search_key(t_key key, t_list *env)
{
	t_list	*aux;
	char	*name;

	aux = env;
	dict = (t_dictionary *) aux->content;
	while (aux->next)
	{
		if (ft_strncmp(key.name, dict->key->name, ft_strlen(dict->key->name)) == 0
			&& (dict->key->only_in_export == key->only_in_export))
			return (aux);
		aux = aux -> next;
	}
	return (NULL);
}

/**
 * @description:
 * 		Search the key value element in the env and update it if found.
 * 		Nothing is done otherwise.
 * @param key: The key of the value that should be updated
 * @param value: The new value
 * @param env: The dictionary of the environment
 * @return: nothing.
*/
void	update_variable_value(t_key key, char *value, t_list *env)
{
	t_list	*found;
	char	*name;

	found = search_key(*key, env);
	if (found)
		found->content->value = value;
}

/**
 * @description:
 * 		Search the key element in the env and deletes it if found.
 * 		Nothing is done otherwise.
 * @param key: The key to be deleted
 * @param env: The dictionary of the environment where the key should be deleted
 * @return: nothing
*/
void	delete_variable(t_key *key, t_list *env)
{
	t_list	*aux;
	t_list	*found;
	char	*name;

	aux = env;
	dict = (t_dictionary *) aux->content;
	found = search_key(*key, env);
	if (found)
	{
		while (aux->next == found)
			aux = aux -> next;
		aux->next = found->next;
		ft_lstdelone(found, free);
		free(found);
	}
}