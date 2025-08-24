/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:24:19 by amairia           #+#    #+#             */
/*   Updated: 2025/08/24 20:25:12 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static void	free_argv_curr(t_command *current)
{
	int	i;

	if (!(current->argv))
		return ;
	i = 0;
	while (current->argv[i])
	{
		free(current->argv[i]);
		current->argv[i] = NULL;
		i++;
	}
	free(current->argv);
	current->argv = NULL;
}

void	free_command_list(t_command *cmd_list)
{
	t_command	*current;
	t_command	*next_node;

	if (!cmd_list)
		return ;
	current = cmd_list;
	while (current)
	{
		next_node = current->next;
		free_argv_curr(current);
		free(current->redirect_in);
		free(current->redirect_out);
		free(current->append_out);
		free(current->heredoc_lim);
		free(current);
		current = NULL;
		current = next_node;
	}
	cmd_list = NULL;
}
