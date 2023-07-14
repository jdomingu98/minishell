/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:23:11 by jdomingu          #+#    #+#             */
/*   Updated: 2023/07/14 01:23:13 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	set_stdin(t_list *cmd_list, char *fname)
{
	t_command	*cmd;

	cmd = (t_command *) ft_lstlast(cmd_list)->content;
	cmd->in_fileno = open(fname, O_RDONLY);
	if (cmd->in_fileno == -1)
		return (NOT_FOUND);
	return (NO_ERROR);
}

t_error	set_stdout(t_list *cmd_list, char *fname, bool is_append)
{
	t_command	*cmd;
	int			permissions;
	int			mode;

	cmd = (t_command *) ft_lstlast(cmd_list)->content;
	permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	mode = O_WRONLY | O_CREAT | O_TRUNC;
	if (is_append)
		mode = O_WRONLY | O_CREAT | O_APPEND;
	cmd->out_fileno = open(fname, mode, permissions);
	return (NO_ERROR);
}

t_error	append_command_arg(t_list *cmd_list, char *new_arg)
{
	t_command	*cmd;
	char		**argv;
	int			i;

	cmd = (t_command *) ft_lstlast(cmd_list)->content;
	argv = ft_calloc(cmd->ac + 2, sizeof(char *));
	if (!argv)
		return (MALLOC);
	i = 0;
	while (cmd->args[i])
	{
		argv[i] = cmd->args[i];
		i++;
	}
	argv[i] = ft_strdup(new_arg);
	if (!argv[i])
		return (MALLOC);
	cmd->ac++;
	free(cmd->args);
	cmd->args = argv;
	return (NO_ERROR);
}

t_error	append_command(t_list **cmd_list, char *new_cmd)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (MALLOC);
	cmd->args = ft_calloc(2, sizeof(char *));
	if (!cmd->args)
		return (MALLOC);
	if (new_cmd)
	{
		cmd->args[0] = ft_strdup(new_cmd);
		if (!cmd->args[0])
			return (MALLOC);
		cmd->ac = 1;
	}
	ft_lstadd_back(cmd_list, ft_lstnew(cmd));
	return (NO_ERROR);
}
