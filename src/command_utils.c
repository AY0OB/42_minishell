/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:24:29 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:34:19 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	*new_command(void)
{
	t_command	*command;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	return (command);
}

t_command	*last_command(t_command *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_command_back(t_command **list, t_command *new)
{
	t_command	*last;

	if (!list || !new)
		return ;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	last = last_command(*list);
	last->next = new;
}

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_command_list(t_command *cmd_list)
{
	t_command	*current;
	t_command	*next_node;

	current = cmd_list;
	while (current)
	{
		next_node = current->next;
		free_argv(current->argv);
		free(current->redirect_in);
		free(current->redirect_out);
		free(current->append_out);
		free(current->heredoc_lim);
		free(current);
		current = next_node;
	}
}
