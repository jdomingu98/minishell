/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdomingu <jdomingu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:23:52 by jdomingu          #+#    #+#             */
/*   Updated: 2023/07/14 01:23:54 by jdomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(int fd)
{
	if (fd > 0)
		close(fd);
}

static void	iterate_to_close(t_list *current, t_list *next, t_list *commands)
{
	t_command	*command;

	while (commands)
	{
		command = (t_command *) commands->content;
		if (commands == current)
			close_fd(command->in_fileno);
		else if (next && commands == next)
			close_fd(command->out_fileno);
		else
		{
			close_fd(command->in_fileno);
			close_fd(command->out_fileno);
		}
		commands = commands->next;
	}
}

void	close_pipes(t_data *data, t_list *instr)
{
	t_list	*current;
	t_list	*next;
	t_list	*commands;

	commands = data->command_list;
	next = 0;
	current = 0;
	if (instr)
		current = instr->content;
	if (instr && instr->next)
		next = instr->next->content;
	iterate_to_close(current, next, commands);
}
