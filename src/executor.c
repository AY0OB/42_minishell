/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:38:25 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:39:06 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

static int	execute_simple_builtin(t_command *cmd, t_all *all)
{
	return (execute_builtin(cmd, all));
}

static void	wait_for_children(int last_pid)
{
	int	status;
	int	pid;

	waitpid(last_pid, &status, 0);
	pid = wait(&status);
	while (pid != -1)
	{
		pid = wait(&status);
	}
}

void	executor(t_command *cmd_list, char **envp, t_all *all)
{
	int		pipefd[2];
	int		in_fd;
	pid_t	last_pid;

	if (!cmd_list)
		return ;
	if (cmd_list->next == NULL && is_builtin(cmd_list->argv[0]))
	{
		execute_simple_builtin(cmd_list, all);
		return ;
	}
	in_fd = STDIN_FILENO;
	last_pid = -1;
	while (cmd_list)
	{
		if (cmd_list->next && pipe(pipefd) == -1)
			return (perror("minishell: pipe"));
		last_pid = fork();
		if (last_pid == -1)
			return (perror("minishell: fork"));
		if (last_pid == 0)
		{
			if (cmd_list->next)
				child_process(cmd_list, envp, in_fd, pipefd[1], all);
			else
				child_process(cmd_list, envp, in_fd, STDOUT_FILENO, all);
		}
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (cmd_list->next)
		{
			close(pipefd[1]);
			in_fd = pipefd[0];
		}
		cmd_list = cmd_list->next;
	}
	if (last_pid > 0)
		wait_for_children(last_pid);
}
