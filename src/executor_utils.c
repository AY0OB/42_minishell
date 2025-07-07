/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:23:12 by amairia           #+#    #+#             */
/*   Updated: 2025/07/07 19:24:05 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

int	handle_command_redirections(t_command *cmd)
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
		int in_fd, int out_fd, t_all *all)
{
	if (in_fd != STDIN_FILENO) //redirect to prev pipe
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO) //redirect to next pipe
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (handle_command_redirections(cmd) == -1) //redirect
		exit(1);
	launch_command(cmd, envp, all);
}
