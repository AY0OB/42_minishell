/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 00:06:41 by amairia           #+#    #+#             */
/*   Updated: 2025/08/21 21:34:22 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

static int	handle_command_redirections_bis(t_command *cmd)
{
	int	fd;

	if (cmd->redirect_in)
	{
		fd = open(cmd->redirect_in, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->redirect_in);
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->redirect_out)
	{
		fd = open(cmd->redirect_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(cmd->redirect_out);
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	handle_command_redirections(t_command *cmd)
{
	int	fd;

	if (handle_command_redirections_bis(cmd) == -1)
		return (-1);
	if (cmd->append_out)
	{
		fd = open(cmd->append_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(cmd->append_out);
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

static void	launch_command(t_command *cmd, char **envp, t_all *all)
{
	char	*cmd_path;

	if (is_builtin(cmd->argv[0]))
		exit(execute_builtin(cmd, all));
	cmd_path = get_command_path(cmd->argv[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	execve(cmd_path, cmd->argv, envp);
	free(cmd_path);
	perror("minishell");
	exit(126);
}

void	child_process(t_command *cmd, char **envp,
			int fd[2], t_all *all)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (fd[0] != STDIN_FILENO)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (handle_command_redirections(cmd) == -1)
		exit(1);
	launch_command(cmd, envp, all);
}
