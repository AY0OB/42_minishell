/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amairia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:51:25 by amairia           #+#    #+#             */
/*   Updated: 2025/09/05 16:55:55 by amairia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_faile_and_exec(t_all *all)
{
	if (all->faile_open)
	{
		set_pipe_fd(all);
		clear_fd(all);
		all->last_exit_status = 1;
		all->faile_open = false;
	}
	else
		exec_pipe(all);
	all->data.pipe_done++;
}

void	exec_pipe(t_all *all)
{
	pid_t	pid;
	char	**cmd;
	char	*cmd_path;

	cmd = NULL;
	cmd_path = NULL;
	pid = -1;
	if (set_cmd_pipe(all, &cmd, &cmd_path) == -1)
	{
		set_pipe_fd(all);
		clear_fd(all);
		return ;
	}
	set_pipe_fd(all);
	redir_dup_exec_check_fork(all, cmd, &pid);
	if (pid == 0)
		exec_cmd(all, cmd, cmd_path);
	if (pid != -1)
		all->tab_pid[all->i_pid++] = pid;
	all->is_builtin = false;
	free(cmd);
	if (cmd_path)
		free(cmd_path);
	clear_fd(all);
}

int	free_and_close(t_all *all, char ***cmd)
{
	free(cmd[0]);
	all->faile_open = false;
	all->last_exit_status = 0;
	clear_fd(all);
	return (-1);
}

void	exec_cmd(t_all *all, char **cmd, char *cmd_path)
{
	close(all->pipe_info.last_fd);
	dup_redir_pipe(all);
	if (all->is_builtin)
		execute_builtin(cmd, all, 127);
	close(all->data.og_in);
	close(all->data.og_out);
	if (all->data.std_in != 0)
		close(all->data.std_in);
	if (all->data.std_out != 1)
		close(all->data.std_out);
	ft_execve(all, &cmd_path, &cmd);
}

void	redir_dup_exec_check_fork(t_all *all, char **cmd, pid_t *pid)
{
	if (all->is_builtin && ft_strncmp(cmd[0], "exit", 5) != 0)
	{
		dup_redir_pipe(all);
		all->last_exit_status = execute_builtin(cmd, all, 127);
		dup2(all->data.og_in, STDIN_FILENO);
		dup2(all->data.og_out, STDOUT_FILENO);
		close(all->data.og_in);
		close(all->data.og_out);
		clear_fd(all);
	}
	else
		*pid = fork();
}
