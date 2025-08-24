/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 23:51:23 by amairia           #+#    #+#             */
/*   Updated: 2025/08/24 20:25:31 by amairia          ###   ########.fr       */
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

int	add_command_back(t_command **list, t_command *new)
{
	t_command	*last;

	if (!list || !new)
		return (-1);
	if (*list == NULL)
	{
		*list = new;
		return (0);
	}
	last = last_command(*list);
	last->next = new;
	return (0);
}
