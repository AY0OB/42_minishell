/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 00:04:42 by amairia           #+#    #+#             */
/*   Updated: 2025/08/24 21:50:57 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

static int	execute_single_builtin(t_command *cmd, t_all *all);
static int	execute_pipeline(t_command *cmd_list, char **envp,
				t_all *all, int in_fd);
static int	wait_for_children(int last_pid);

int	executor(t_command *cmd_list, char **envp, t_all *all)
{
	if (!cmd_list || !cmd_list->argv || !cmd_list->argv[0])
		return (0);
	if (cmd_list->next == NULL && is_builtin(cmd_list->argv[0]))
	{
		return (execute_single_builtin(cmd_list, all));
	}
	else
	{
		return (execute_pipeline(cmd_list, envp, all, STDIN_FILENO));
	}
}

static int	execute_single_builtin(t_command *cmd, t_all *all)
{
	int	original_stdin;
	int	original_stdout;
	int	exit_status;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (original_stdin == -1 || original_stdout == -1)
	{
		perror("minishell: dup");
		return (1);
	}
	if (handle_command_redirections(cmd) == -1)
	{
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdin);
		close(original_stdout);
		return (1);
	}
	exit_status = execute_builtin(cmd, all);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	return (exit_status);
}

static int	execute_pipeline(t_command *cmd_list, char **envp,
				t_all *all, int in_fd)
{
	int		pipefd[2];
	int		fd[2];
	pid_t	last_pid;

	last_pid = -1;
	setup_execution_mode();
	while (cmd_list)
	{
		if (execute_pipeline_check(cmd_list, pipefd, &last_pid) == 1)
			return (1);
		fd[0] = in_fd;
		fd[1] = STDOUT_FILENO;
		if (last_pid == 0 && cmd_list->next)
		{
			fd[1] = pipefd[1];
			child_process(cmd_list, envp, fd, all);
		}
		else if (last_pid == 0)
			child_process(cmd_list, envp, fd, all);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		execute_pipeline_fd(cmd_list, pipefd, &in_fd);
		cmd_list = cmd_list->next;
	}
	return (wait_for_children(last_pid));
}

static int	wait_for_children(int last_pid)
{
	int	status;
	int	exit_status;

	if (last_pid < 0)
		return (0);
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = 128 + WTERMSIG(status);
	else
		exit_status = 1;
	while (wait(NULL) != -1)
		;
	return (exit_status);
}
