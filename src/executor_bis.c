/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:55:10 by amairia           #+#    #+#             */
/*   Updated: 2025/08/24 23:26:21 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_pipeline_check(t_command *cmd_list,
		int pipefd[2], pid_t *last_pid, char **envp)
{
	char	*path;

	path = get_command_path(cmd_list->argv[0], envp);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(cmd_list->argv[0], 2);
		ft_putstr_fd("\n", 2);
	}
	if (path)
		free(path);
	if (cmd_list->next && pipe(pipefd) == -1)
	{
		perror("minishell: pipe");
		return (1);
	}
	*last_pid = fork();
	if (*last_pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	return (0);
}

void	execute_pipeline_fd(t_command *cmd_list, int pipefd[2], int *in_fd)
{
	if (cmd_list->next)
	{
		close(pipefd[1]);
		*in_fd = pipefd[0];
	}
}
