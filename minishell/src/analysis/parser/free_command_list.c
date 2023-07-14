/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:22:47 by jdomingu          #+#    #+#             */
/*   Updated: 2023/07/14 01:22:49 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command_node(void *command_list_node)
{
	t_command	*cmd;
	int			i;

	if (!command_list_node)
		return ;
	cmd = (t_command *) command_list_node;
	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	free(cmd);
}

void	free_command_list(t_list **command_list)
{
	if (!command_list)
		return ;
	ft_lstclear(command_list, &free_command_node);
}
