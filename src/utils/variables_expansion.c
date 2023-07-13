/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:24:30 by jdomingu          #+#    #+#             */
/*   Updated: 2023/07/14 01:24:32 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var(t_data *data, char *line, int *var_len)
{
	char	*var_name;
	char	*var_value;

	*var_len = 0;
	while (*(line + *var_len) && (ft_isalnum(*(line + *var_len))
			|| *(line + *var_len) == '?'))
		(*var_len)++;
	if (*var_len == 0)
		return (NULL);
	var_name = ft_substr(line, 0, *var_len);
	if (ft_strncmp(var_name, "?", 2) == 0)
		return (free(var_name), ft_itoa(g_status.status_code));
	var_value = get_env_value(data, var_name);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	return (var_value);
}

static void	concat_me(char **line, int count, char *var_value, int var_name_len)
{
	char	*aux;
	char	*str1;
	char	*str2;

	str1 = ft_substr(*line, 0, count);
	aux = ft_strjoin(str1, var_value);
	free(str1);
	str2 = ft_substr(*line, count + var_name_len + 1, -1);
	free(*line);
	*line = ft_strjoin(aux, str2);
	free(aux);
	free(str2);
}

void	expand_variables(char **line, t_data *data, bool expand_quotes)
{
	int		var_name_len;
	int		line_count;
	char	*var_value;
	bool	quote_found;

	line_count = 0;
	quote_found = false;
	while (*(*line + line_count))
	{
		if (*(*line + line_count) == '\'')
			quote_found = !quote_found;
		if (*(*line + line_count) == '$' && (!quote_found || expand_quotes))
		{
			var_value = get_var(data, (*line) + line_count + 1, &var_name_len);
			if (!var_value)
				return ;
			if (var_name_len != 0)
				concat_me(line, line_count, var_value, var_name_len);
			line_count += ft_strlen(var_value);
			free(var_value);
		}
		else
			line_count++;
	}
}
